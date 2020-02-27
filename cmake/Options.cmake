##
# all kinds of options
##

## build options
option(BUILD_TESTS "Enable Tests" ON)
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
## use lib XYZ options
option(CPP_STARTER_USE_QT "Enable compilation of QT sample" OFF)
option(CPP_STARTER_USE_FLTK "Enable compilation of FLTK sample" OFF)
option(CPP_STARTER_USE_GTKMM "Enable compilation of GTKMM sample" OFF)
option(CPP_STARTER_USE_IMGUI "Enable compilation of ImGui sample" OFF)
option(CPP_STARTER_USE_NANA "Enable compilation of Nana GUI sample" OFF)
option(CPP_STARTER_USE_SDL "Enable compilation of SDL sample" OFF)
# add more enable/disable features