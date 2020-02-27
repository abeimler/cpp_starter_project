#!/usr/bin/env python
"""A wrapper script around include-what-you-use,
suitable for linting multiple files
and to use for continuous integration.

This is an alternative to iwyu-tool.py,
that returns a sensible exit code,
and make it easy to run on a subset of a compilation database.

"""

from __future__ import print_function, unicode_literals

import argparse
import errno
import fnmatch
import io
import json
import multiprocessing
import os
import shlex
import signal
import stat
import subprocess
import sys
import traceback

from functools import partial


class ExitStatus:
    SUCCESS = 0
    FAILURE = 1
    TROUBLE = 2


class CompileCommand:
    def __init__(self, directory, file, arguments):
        self.directory = directory
        self.file = file
        self.arguments = arguments

    @property
    def normfile(self):
        return os.path.normpath(os.path.join(self.directory, self.file))

    def __repr__(self):
        return "{{directory: {}, file: {}, arguments: {}}}".format(
            repr(self.directory), repr(self.file), repr(self.arguments)
        )

    def __str__(self):
        return self.__repr__()

    def _as_tuple(self):
        return (self.directory, self.file, self.arguments)

    def __eq__(self, other):
        if isinstance(other, self.__class__):
            return self._as_tuple() == other._as_tuple()
        return NotImplemented

    def __ne__(self, other):
        return not self == other


def list_compile_commands(build_dir, paths, extensions=None, exclude=None):
    if exclude is None:
        exclude = []

    files = []
    dirs = []
    for path in paths:
        st = os.stat(path)
        if stat.S_ISDIR(st.st_mode):
            dirs.append(st)
        else:
            files.append(st)

    if not files and not dirs:
        return []

    db_path = os.path.join(build_dir, "compile_commands.json")
    with open(db_path) as f:
        data = json.load(f)

    compile_commands = []
    for d in data:
        path = os.path.join(d["directory"], d["file"])

        to_skip = False
        for pattern in exclude:
            if fnmatch.fnmatch(path, pattern):
                to_skip = True
                break
        if to_skip:
            continue

        to_keep = False
        if files:
            try:
                st = os.stat(path)
            except EnvironmentError as e:
                if e.errno != errno.ENOENT:
                    raise
                continue
        for file_st in files:
            if os.path.samestat(file_st, st):
                to_keep = True
                break
        if not to_keep:
            curdir = os.path.dirname(os.path.normpath(path))
            olddir = None
            while not curdir == olddir:
                try:
                    st_curdir = os.stat(curdir)
                except EnvironmentError as e:
                    if e.errno != errno.ENOENT:
                        raise
                    break
                for dir_st in dirs:
                    if os.path.samestat(dir_st, st_curdir):
                        to_keep = True
                        break
                if to_keep:
                    break
                olddir = curdir
                curdir = os.path.dirname(curdir)

        if not to_keep:
            continue

        if "arguments" in d:
            arguments = d["arguments"]
        else:
            # PERFORMANCE: I think shlex is inherently slow,
            # something performing better may be necessary
            arguments = shlex.split(
                d["command"],
                # https://github.com/Sarcasm/compdb/issues/17
                # XXX: os.name is "posix" on mysys2/cygwin,
                # is that correct?
                posix=os.name == "posix",
            )

        compile_commands.append(CompileCommand(d["directory"], d["file"], arguments))

    return compile_commands


class UnexpectedError(Exception):
    def __init__(self, message, exc=None):
        super(UnexpectedError, self).__init__(message)
        self.formatted_traceback = traceback.format_exc()
        self.exc = exc


def run_iwyu(args, compile_command):
    invocation = [args.iwyu_executable] + compile_command.arguments[1:]
    # Use of utf-8 to decode the process output.
    #
    # Hopefully, this is the correct thing to do.
    #
    # It's done due to the following assumption (which may be incorrect):
    # - if the diagnostics were internationalized, they would use utf-8:
    #   > Adding Translations to Clang
    #   >
    #   > Not possible yet!
    #   > Diagnostic strings should be written in UTF-8,
    #   > the client can translate to the relevant code page if needed.
    #   > Each translation completely replaces the format string
    #   > for the diagnostic.
    #   > -- http://clang.llvm.org/docs/InternalsManual.html#internals-diag-translation
    #
    # It's not pretty, due to Python 2 & 3 compatibility.
    encoding_py3 = {}
    if sys.version_info[0] >= 3:
        encoding_py3["encoding"] = "utf-8"

    # return code should never be 0,
    # instead on success 2 is returned
    # see https://github.com/include-what-you-use/include-what-you-use/issues/440

    try:
        subprocess.check_output(
            invocation,
            stderr=subprocess.STDOUT,
            cwd=compile_command.directory,
            **encoding_py3
        )
    except subprocess.CalledProcessError as e:
        if e.returncode != 2:
            return "FAILED [with returncode={}]: cd {} && {}\n{}".format(
                e.returncode, compile_command.directory, " ".join(invocation), e.output
            )
        return ""
    except OSError as exc:
        raise
    raise UnexpectedError(
        "{}: returncode=0 is unexpected at this time".format(compile_command.normpath)
    )


def bold_red(s):
    return "\x1b[1m\x1b[31m" + s + "\x1b[0m"


def print_trouble(prog, message, use_colors):
    error_text = "error:"
    if use_colors:
        error_text = bold_red(error_text)
    print("{}: {} {}".format(prog, error_text, message), file=sys.stderr)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--iwyu-executable",
        metavar="EXECUTABLE",
        help="path to the include-what-you-use executable",
        default="include-what-you-use",
    )
    parser.add_argument(
        "-p", dest="build_dir", metavar="BUILD_DIR", help="build path", required=True
    )
    parser.add_argument(
        "files",
        metavar="file",
        nargs="*",
        help="restrict the compilation database entries to process to the given paths",
    )
    parser.add_argument(
        "-j",
        metavar="N",
        type=int,
        default=0,
        help="run N include-what-you-use jobs in parallel"
        " (default number of cpus + 1)",
    )
    parser.add_argument(
        "--color",
        default="auto",
        choices=["auto", "always", "never"],
        help="show colored diff (default: auto)",
    )
    parser.add_argument(
        "-e",
        "--exclude",
        metavar="PATTERN",
        action="append",
        default=[],
        help="exclude paths matching the given glob-like pattern(s)"
        " from recursive search",
    )

    args = parser.parse_args()

    # use default signal handling, like diff return SIGINT value on ^C
    # https://bugs.python.org/issue14229#msg156446
    signal.signal(signal.SIGINT, signal.SIG_DFL)
    try:
        signal.SIGPIPE
    except AttributeError:
        # compatibility, SIGPIPE does not exist on Windows
        pass
    else:
        signal.signal(signal.SIGPIPE, signal.SIG_DFL)

    colored_stdout = False
    colored_stderr = False
    if args.color == "always":
        colored_stdout = True
        colored_stderr = True
    elif args.color == "auto":
        colored_stdout = sys.stdout.isatty()
        colored_stderr = sys.stderr.isatty()

    retcode = ExitStatus.SUCCESS
    compile_commands = list_compile_commands(
        args.build_dir, args.files or ["."], exclude=args.exclude
    )

    if not compile_commands:
        print_trouble(parser.prog, "No compile commands", use_colors=colored_stderr)
        return ExitStatus.TROUBLE

    njobs = args.j
    if njobs == 0:
        njobs = multiprocessing.cpu_count() + 1
    njobs = min(len(compile_commands), njobs)

    if njobs == 1:
        # execute directly instead of in a pool,
        # less overhead, simpler stacktraces
        it = (run_iwyu(args, compile_command) for compile_command in compile_commands)
        pool = None
    else:
        pool = multiprocessing.Pool(njobs)
        it = pool.imap_unordered(partial(run_iwyu, args), compile_commands)
    while True:
        try:
            output = next(it)
        except StopIteration:
            break
        except UnexpectedError as e:
            print_trouble(parser.prog, str(e), use_colors=colored_stderr)
            sys.stderr.write(e.formatted_traceback)
            retcode = ExitStatus.TROUBLE
            # stop at the first unexpected error,
            # something could be very wrong,
            # don't process all files unnecessarily
            if pool:
                pool.terminate()
            break
        else:
            if output:
                print(output, end="", file=sys.stderr)
                if retcode == ExitStatus.SUCCESS:
                    retcode = ExitStatus.FAILURE
    return retcode


if __name__ == "__main__":
    sys.exit(main())