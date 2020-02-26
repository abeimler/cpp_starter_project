include(FetchContent)

##
# dependencies from git and Co. (using FetchContent)
# TODO: add more libs here, when not found in conan
# remove libs you don't use
##

## need for benchmarks
FetchContent_Declare(
    benchpress
    GIT_REPOSITORY https://github.com/abeimler/benchpress.git
    GIT_TAG        1.2.3
)
if(NOT benchpress_POPULATED)
  FetchContent_Populate(benchpress)
  add_subdirectory(${benchpress_SOURCE_DIR} ${benchpress_BINARY_DIR})
endif()

## for gamedev
if(USE_LIB_RAYLIB) ###< use raylib ... (or some other dependencies)
  include(cmake/Raylib.cmake) ###< FetchContent and more
endif()

