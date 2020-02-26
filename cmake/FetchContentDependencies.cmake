include(FetchContent)

##
# dependencies from git and Co. (using FetchContent)
# TODO: add more libs here, when not found in conan
# remove libs you don't use
##

# ## Embedded Template Library, just for fun not needed
# FetchContent_Declare(
#     etl
#     GIT_REPOSITORY https://github.com/ETLCPP/etl.git
#     GIT_TAG        14.35.1
# )
# if(NOT etl_POPULATED)
#   FetchContent_Populate(etl)
#   add_subdirectory(${etl_SOURCE_DIR} ${etl_BINARY_DIR})
# endif()

# ## nice to have, not needed
# FetchContent_Declare(
#     units
#     GIT_REPOSITORY https://github.com/nholthaus/units.git
#     GIT_TAG        v2.3.1
# )
# if(NOT units_POPULATED)
#   FetchContent_Populate(units)

#   #if (NOT BUILD_TESTS) # optimizaions, units needed for tests
#   #  set(DISABLE_IOSTREAM                  ON CACHE BOOL "" FORCE)
#   #  set(DISABLE_PREDEFINED_UNITS          ON CACHE BOOL "" FORCE)

#   #  set(ENABLE_PREDEFINED_LENGTH_UNITS    ON CACHE BOOL "" FORCE)
#   #  set(ENABLE_PREDEFINED_MASS_UNITS      ON CACHE BOOL "" FORCE)
#   #  set(ENABLE_PREDEFINED_TIME_UNITS      ON CACHE BOOL "" FORCE)
#   #endif()

#   add_subdirectory(${units_SOURCE_DIR} ${units_BINARY_DIR})
# endif()

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

