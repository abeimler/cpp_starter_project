add_subdirectory(engine)

option(${CMAKE_PROJECT_NAME_UPPERCASE}_BUILD_RASPBERRY_APP "Build ${CMAKE_PROJECT_NAME} RaspberryPi App" OFF)
if(${${CMAKE_PROJECT_NAME_UPPERCASE}_BUILD_RASPBERRY_APP})
  # TODO: need more works and testing
  include(../../cmake/RaspberryPi.cmake)

  if(BUILD_ON_RASPBERRY_PI)
    add_subdirectory(raspberrypi)
  elseif(UNIX)
    add_subdirectory(raspberrypi)
  endif()
endif()

option(${CMAKE_PROJECT_NAME_UPPERCASE}_BUILD_DESKTOP_APP "Build ${CMAKE_PROJECT_NAME} Desktop App" ON)
if(${${CMAKE_PROJECT_NAME_UPPERCASE}_BUILD_DESKTOP_APP})
  add_subdirectory(desktop)
endif()
