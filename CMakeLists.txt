cmake_minimum_required(VERSION 3.15)

# Set the project name to your project name, my project isn't very descriptive
project(myproject VERSION 0.1.0 LANGUAGES C CXX)
string(TOUPPER "${CMAKE_PROJECT_NAME}" CMAKE_PROJECT_NAME_UPPERCASE)
include(cmake/StandardProjectSettings.cmake)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(cmake/CompilerWarnings.cmake)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)
enable_sanitizers(project_options)

# enable doxygen
include(cmake/Doxygen.cmake)
enable_doxygen()

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)
include(cmake/UseGoldLinker.cmake)

# Very basic PCH example
option(ENABLE_PCH "Enable Precompiled Headers" OFF)
if (ENABLE_PCH)
  # This sets a global PCH parameter, each project will build its own PCH, which
  # is a good idea if any #define's change
  # 
  # 
  target_precompile_headers(project_options INTERFACE <vector> <string> <map> <utility>)
endif()

# user options
include(cmake/Options.cmake)

# Set up some extra Conan dependencies based on our needs
# before loading Conan
set(CONAN_EXTRA_REQUIRES "")
set(CONAN_EXTRA_OPTIONS "")

# nice to have
#list(APPEND CONAN_EXTRA_REQUIRES
#date/2.4.1
#)

include(cmake/Conan.cmake)
run_conan()

# more dependencies
include(cmake/FetchContentDependencies.cmake)
add_subdirectory(thirdparty)


##################################
# Project
##################################

## add configure files
configure_file (
    "${PROJECT_SOURCE_DIR}/include/Version.h.in"
    "${PROJECT_BINARY_DIR}/include/Version.h"
)


if(BUILD_TESTS)
  enable_testing()
  message(
    "Building Tests. Be sure to check out test/tests and test/constexpr_tests for constexpr testing"
  )
  add_subdirectory(test)
endif()

if(BUILD_FUZZING)
  message(
    "Building Fuzz Tests, using fuzzing sanitizer https://www.llvm.org/docs/LibFuzzer.html"
  )
  add_subdirectory(fuzz_test)
endif()

if(BUILD_BENCHMARKS)
  message(
    "Building Benchmarks"
  )
  add_subdirectory(benchmark)
endif()

add_subdirectory(src)