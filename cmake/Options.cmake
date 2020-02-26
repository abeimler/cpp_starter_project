##
# all kinds of options
##

## build options
option(BUILD_TESTS "Enable Tests" OFF)
option(BUILD_INTEGRATION_TESTS "Enable Integration Tests" OFF)
option(BUILD_FUZZING "Enable Fuzz Tests" OFF)
option(BUILD_BENCHMARKS "Enable Benchmark" OFF)

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

## setup spdlog
option(USE_SPDLOG_LOGGING "Use spdlog for Logging" ON)
if(CMAKE_BUILD_TYPE MATCHES Debug)
  option(ENABLE_LOGGING "Enable Logging for ${CMAKE_PROJECT_NAME}" ON)
  set(SPDLOG_LEVEL_DEBUG 1)
  set(SPDLOG_LEVEL_INFO 0)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  option(ENABLE_LOGGING "Enable Logging for ${CMAKE_PROJECT_NAME}" OFF)
  set(SPDLOG_LEVEL_DEBUG 0)
  set(SPDLOG_LEVEL_INFO 1)
endif()
# add more alternatives for logging

## build platform XY options
option(BUILD_RASPBERRY_APP "Build ${CMAKE_PROJECT_NAME} RaspberryPi App" OFF)
option(BUILD_DESKTOP_APP "Build ${CMAKE_PROJECT_NAME} Desktop App" ON)

## use lib XYZ options
option(USE_LIB_RAYLIB "Use raylib Library" ON) # for gamedev
# add more enable/disable features