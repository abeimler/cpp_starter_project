# cpp_starter_project

## Build Status

| branch | codecov | travis-ci | appveyor |
|--------|---------|-----------|----------|
| master | [![codecov](https://codecov.io/gh/abeimler/cpp_starter_project/branch/master/graph/badge.svg)](https://codecov.io/gh/abeimler/cpp_starter_project) | [![Build Status](https://travis-ci.org/abeimler/cpp_starter_project.svg?branch=master)](https://travis-ci.org/abeimler/cpp_starter_project) | [![Build status](https://ci.appveyor.com/api/projects/status/7kk70jwamualyk72/branch/master?svg=true)](https://ci.appveyor.com/project/abeimler/cpp-starter-project/branch/master) |
| develop | [![codecov](https://codecov.io/gh/abeimler/cpp_starter_project/branch/develop/graph/badge.svg)](https://codecov.io/gh/abeimler/cpp_starter_project) | [![Build Status](https://travis-ci.org/abeimler/cpp_starter_project.svg?branch=develop)](https://travis-ci.org/abeimler/cpp_starter_project) | [![Build status](https://ci.appveyor.com/api/projects/status/7kk70jwamualyk72/branch/develop?svg=true)](https://ci.appveyor.com/project/abeimler/cpp-starter-project/branch/develop) |

_change your travis and Co. links here_

## Project Structure

```text
.
├── benchmark                       benchmarks and benchmark-main
│   └── benchmarks                  Sourcecode for benchmarks
├── cmake
├── fuzz_test
├── include                         public include-files, configs, ...
├── src                             sourcecode
│   ├── app                         application code
│   │   ├── engine                  sourcecode of app-core functionality (UI, GameRender-Engine and such)
│   │   ├── fltk                    window applications ...
│   │   ├── gtkmm
│   │   ├── imgui
│   │   ├── intro
│   │   ├── nana
│   │   ├── qt
│   │   └── sdl
│   └── core                        sourcecode of core functionality (GameLogic and such)
├── test                            tests and test-main
│   ├── constexpr_tests             constexpr unittests
│   ├── integrartion_tests          tests for integration tests (tests for UI, test usually you can not run on CI)
│   └── tests                       unittests (tests for core functionality)
└── thirdparty                      custom changed libraries, libraries without dependencies managment, ...
```

## Build

### Requirements

 - [python](https://www.python.org/downloads/) and [python-pip](https://pip.pypa.io/en/stable/installing/)
 - C/C++ Compiler with C++ 17 support
 - cmake
 - cogapp   
   - `pip install --user cogapp`

We need cogapp to generate Sourcefile-lists in CMakeLists.txt-files, _see ./configure.sh_

### configure

run 
```
mkdir build
``` 
then run `./configure.sh` or 
```
cmake . -Bbuild ..
```

### build

run `./build.sh` or 
```
cmake --build build -- -j 8
```

## run tests

run `./tests.sh` or 
```
cd test && ctest -j4
```


## Tools

 - `./run-clang-format.sh` format all code
 - `./run-cmake-format.sh` format all CMakeLists.txt-files
  



## Links

 - [C++ Weekly - Ep 208 - The Ultimate CMake / C++ Quick Start](https://www.youtube.com/watch?v=YbgH7yat-Jo)
 - https://github.com/lefticus/cpp_starter_project
 - https://github.com/bsamseth/cpp-project
 - [Oh No! More Modern CMake - Deniz Bahadir - Meeting C++ 2019](https://www.youtube.com/watch?v=y9kSr5enrSk)
 - [More Modern CMake - Deniz Bahadir - Meeting C++ 2018](https://www.youtube.com/watch?v=y7ndUhdQuU8)
 - [C++Now 2017: Daniel Pfeifer “Effective CMake"](https://www.youtube.com/watch?v=bsXLMQ6WgIk)