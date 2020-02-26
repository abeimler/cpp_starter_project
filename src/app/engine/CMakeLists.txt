set(APP_CORE_${CMAKE_PROJECT_NAME}_HEADERS "")
set(APP_CORE_${CMAKE_PROJECT_NAME}_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND APP_CORE_${CMAKE_PROJECT_NAME}_HEADERS ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND APP_CORE_${CMAKE_PROJECT_NAME}_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.h 
)
# [[[end]]]
# cmake-format: on

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.c*').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND APP_CORE_${CMAKE_PROJECT_NAME}_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND APP_CORE_${CMAKE_PROJECT_NAME}_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Engine Header Files"
  FILES APP_CORE_${${CMAKE_PROJECT_NAME}_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Engine Source Files"
  FILES APP_CORE_${${CMAKE_PROJECT_NAME}_SOURCE})

add_library(${CMAKE_PROJECT_NAME}engine STATIC)
add_library(${CMAKE_PROJECT_NAME}::engine ALIAS ${CMAKE_PROJECT_NAME}engine)
target_link_libraries(${CMAKE_PROJECT_NAME}engine PRIVATE project_warnings project_options)
target_sources(${CMAKE_PROJECT_NAME}engine PRIVATE ${APP_CORE_${CMAKE_PROJECT_NAME}_SOURCE}
                                                   ${APP_CORE_${CMAKE_PROJECT_NAME}_HEADERS})

target_include_directories(${CMAKE_PROJECT_NAME}engine PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}engine PRIVATE ${PROJECT_BINARY_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}engine PUBLIC ${PROJECT_SOURCE_DIR}/src/app)
target_include_directories(${CMAKE_PROJECT_NAME}engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# TODO: add libs
target_link_libraries(${CMAKE_PROJECT_NAME}engine PUBLIC ${CMAKE_PROJECT_NAME}::core)
target_link_libraries(${CMAKE_PROJECT_NAME}engine PUBLIC Bitsery::bitsery)
target_link_libraries(${CMAKE_PROJECT_NAME}engine PUBLIC ${CMAKE_PROJECT_NAME}::bitsery)

##
# setup/add more libs
##
if(USE_LIB_RAYLIB)
  # not needed, meybe forlater
  target_compile_definitions(${CMAKE_PROJECT_NAME}engine PUBLIC -DUSE_RAYLIB)

  # add lib
  target_link_libraries(${CMAKE_PROJECT_NAME}engine PUBLIC raylib)
endif()
# add more libs or alternatives for raylib, rayfork, etc.

if(ENABLE_LOGGING)
  target_compile_definitions(${CMAKE_PROJECT_NAME}engine PUBLIC -DENABLE_LOGGING)

  # add spdlog for logging
  if(USE_SPDLOG_LOGGING)
    target_compile_definitions(${CMAKE_PROJECT_NAME}engine PUBLIC -DUSE_SPDLOG_LOGGING)
    target_link_libraries(${CMAKE_PROJECT_NAME}engine PUBLIC CONAN_PKG::spdlog CONAN_PKG::fmt)
  endif()
endif()