include(FindPackageHandleStandardArgs)

set(APP_RASPBERRYPI_${CMAKE_PROJECT_NAME}_HEADERS "")
set(APP_RASPBERRYPI_${CMAKE_PROJECT_NAME}_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND APP_RASPBERRYPI_${CMAKE_PROJECT_NAME}_HEADERS ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
list(APPEND APP_RASPBERRYPI_${CMAKE_PROJECT_NAME}_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio/GpIO.h 
)
# [[[end]]]
# cmake-format: on

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.c??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND APP_RASPBERRYPI_${CMAKE_PROJECT_NAME}_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
list(APPEND APP_RASPBERRYPI_${CMAKE_PROJECT_NAME}_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio/GpIO.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Terminal Main Header Files"
  FILES APP_RASPBERRYPI_${${CMAKE_PROJECT_NAME}_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Terminal Main Source Files"
  FILES APP_RASPBERRYPI_${${CMAKE_PROJECT_NAME}_SOURCE})

add_executable(${CMAKE_PROJECT_NAME}-raspberry)
target_sources(${CMAKE_PROJECT_NAME}-raspberry PRIVATE ${APP_RASPBERRYPI_${CMAKE_PROJECT_NAME}_SOURCE}
                                                       ${APP_RASPBERRYPI_${CMAKE_PROJECT_NAME}_HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME}-raspberry PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME}-raspberry PUBLIC ${PROJECT_SOURCE_DIR}/src/app)

# add GPIO libs
if(BUILD_ON_RASPBERRY_PI)
  find_library(BCM2835_LIBRARIES NAMES bcm2835)
  find_path(BCM2835_INCLUDE_DIRS NAMES bcm2835.h)

  find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
  find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)

  find_package_handle_standard_args(wiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIRS)
  find_package_handle_standard_args(bcm2835 DEFAULT_MSG BCM2835_LIBRARIES BCM2835_INCLUDE_DIRS)

  if(WIRINGPI_FOUND)
    target_compile_definitions(${CMAKE_PROJECT_NAME}-raspberry PRIVATE USE_WIRING_PI)
    target_link_libraries(${CMAKE_PROJECT_NAME}-raspberry ${WIRINGPI_LIBRARIES})
    target_include_directories(${CMAKE_PROJECT_NAME}-raspberry PRIVATE ${WIRINGPI_INCLUDE_DIRS})
  elseif(BCM2835_FOUND)
    target_compile_definitions(${CMAKE_PROJECT_NAME}-raspberry PRIVATE USE_BCM2835)
    target_link_libraries(${CMAKE_PROJECT_NAME}-raspberry ${BCM2835_LIBRARIES})
    target_include_directories(${CMAKE_PROJECT_NAME}-raspberry PRIVATE ${BCM2835_INCLUDE_DIRS})
  endif()
endif()

# TODO: add libs target_link_libraries(${CMAKE_PROJECT_NAME}-raspberry ${CMAKE_PROJECT_NAME}::core)
# target_link_libraries(${CMAKE_PROJECT_NAME}-raspberry ${CMAKE_PROJECT_NAME}::engine)

# try to optimize, maybe later todo .... set(THREADS_PREFER_PTHREAD_FLAG ON) find_package(Threads REQUIRED)
# target_link_libraries(${CMAKE_PROJECT_NAME}_raspberry Threads::Threads)

# if(SINGLE_CORE_BOARD) message(STATUS "Targeting a Raspberry Pi with only one hardware core")
# target_compile_definitions(${CMAKE_PROJECT_NAME}-raspberry PRIVATE SINGLE_CORE_BOARD) #
# target_compile_options(${CMAKE_PROJECT_NAME}-raspberry PRIVATE -fno-threadsafe-statics)

# target_compile_definitions(${CMAKE_PROJECT_NAME}-raspberry PRIVATE SPDLOG_NO_THREAD_ID SPDLOG_NO_TLS) endif()

# if(UNIX AND NOT APPLE) target_compile_definitions(${CMAKE_PROJECT_NAME}-raspberry PRIVATE SPDLOG_CLOCK_COARSE) endif()

# target_compile_options(${CMAKE_PROJECT_NAME}-raspberry PRIVATE -fno-rtti -fno-exceptions -fno-asynchronous-unwind-
# tables) if(BUILD_ON_RASPBERRY_PI) target_compile_options(${CMAKE_PROJECT_NAME}-raspberry PRIVATE -marm -mabi=aapcs-
# linux -mhard-float -mfloat-abi=hard -mlittle-endian -funsafe-math-optimizations) endif()
