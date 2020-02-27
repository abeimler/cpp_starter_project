if(BUILD_RASPBERRY_APP OR BUILD_DESKTOP_APP)
  add_subdirectory(engine)

  if(BUILD_RASPBERRY_APP)
    # TODO: needs more work and testing
    include(../../cmake/RaspberryPi.cmake)

    if(BUILD_ON_RASPBERRY_PI OR UNIX)
      add_subdirectory(raspberrypi)
    endif()
  endif()

  if(BUILD_DESKTOP_APP)
    add_subdirectory(desktop)
  endif()
endif()