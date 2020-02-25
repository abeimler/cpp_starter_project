##
# all kinds of options
##

option(BUILD_SHARED_LIBS "Enable compilation of shared libraries" OFF)

## setup spdlog
option(USE_SPDLOG_LOGGING "Use spdlog for Logging" ON)
if(CMAKE_BUILD_TYPE MATCHES Debug)
  option(${CMAKE_PROJECT_NAME_UPPERCASE}_ENABLE_LOGGING "Enable Logging for ${CMAKE_PROJECT_NAME}" ON)
  set(SPDLOG_LEVEL_DEBUG 1)
  set(SPDLOG_LEVEL_INFO 0)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  option(${CMAKE_PROJECT_NAME_UPPERCASE}_ENABLE_LOGGING "Enable Logging for ${CMAKE_PROJECT_NAME}" OFF)
  set(SPDLOG_LEVEL_DEBUG 0)
  set(SPDLOG_LEVEL_INFO 1)
endif()

# use lib XYZ options
option(${CMAKE_PROJECT_NAME_UPPERCASE}_USE_RAYLIB "" ON) # for gamedev