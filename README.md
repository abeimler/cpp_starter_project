# cpp_starter_project

## Build Status

| branch | codecov | travis-ci | appveyor |
|--------|---------|-----------|----------|
| master | [![codecov](https://codecov.io/gh/abeimler/cpp_starter_project/branch/master/graph/badge.svg)](https://codecov.io/gh/abeimler/cpp_starter_project) | [![Build Status](https://travis-ci.org/abeimler/cpp_starter_project.svg?branch=master)](https://travis-ci.org/abeimler/cpp_starter_project) | [![Build status](https://ci.appveyor.com/api/projects/status/7kk70jwamualyk72/branch/master?svg=true)](https://ci.appveyor.com/project/abeimler/cpp-starter-project/branch/master) |
| develop | [![codecov](https://codecov.io/gh/abeimler/cpp_starter_project/branch/develop/graph/badge.svg)](https://codecov.io/gh/abeimler/cpp_starter_project) | [![Build Status](https://travis-ci.org/abeimler/cpp_starter_project.svg?branch=develop)](https://travis-ci.org/abeimler/cpp_starter_project) | [![Build status](https://ci.appveyor.com/api/projects/status/7kk70jwamualyk72/branch/develop?svg=true)](https://ci.appveyor.com/project/abeimler/cpp-starter-project/branch/develop) |

_change your travis and Co. links here_

## Project Structure

```
 .
 +-- _benchmarks                    benchmarks and benchmark-main
 |  +-- _**benchmarks**             Sourcecode for benchmarks
 +-- _src                           Sourcecode
     +-- _app                       Application code
     |   +-- _engine                Sourcecode of app-core functionality (UI and GameRender-Engine and such)
     |   +-- _fltk, gtkmm, qt ...   Window Applications
     +-- _**core**                  Sourcecode of core functionality (GameLogic and such)
     +-- _test                      Test code and test-main
     |   +-- constexpr_test         constexpr Unittests
     |   +-- integrartion_tests     Tests for integration tests (test for UI and may not possible on CI)
     |   +-- tests                  Unittests (tests for core functionality)
     +-- _thirdparty                custom changed libraries or libs not on the Internet (github, conan, ...)
```

## Build

### Requirements

 - cmake
 - cogapp   
   - `pip install --user cogapp`

We need cogsapp to generate Sourcefile-lists in CMakeLists.txt-files, _see ./configure.sh_

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
  
