# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("set(APP_ENGINE_${CMAKE_PROJECT_NAME}_HEADERS ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
set(APP_ENGINE_${CMAKE_PROJECT_NAME}_HEADERS 
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
#       cog.outl("set(APP_ENGINE_${CMAKE_PROJECT_NAME}_SOURCE ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
set(APP_ENGINE_${CMAKE_PROJECT_NAME}_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Engine Header Files"
  FILES ${APP_ENGINE_${CMAKE_PROJECT_NAME}_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Engine Source Files"
  FILES ${APP_ENGINE_${CMAKE_PROJECT_NAME}_SOURCE})

add_library(${CMAKE_PROJECT_NAME}engine STATIC)
add_library(${CMAKE_PROJECT_NAME}::engine ALIAS ${CMAKE_PROJECT_NAME}engine)
target_link_libraries(${CMAKE_PROJECT_NAME}engine PRIVATE project_warnings project_options)
target_sources(${CMAKE_PROJECT_NAME}engine PRIVATE ${APP_ENGINE_${CMAKE_PROJECT_NAME}_SOURCE}
                                                   ${APP_ENGINE_${CMAKE_PROJECT_NAME}_HEADERS})

# TODO: add libs
target_link_libraries(${CMAKE_PROJECT_NAME}engine PUBLIC ${CMAKE_PROJECT_NAME}::core)

#
# setup/add more libs
#
if(ENABLE_LOGGING)
  target_compile_definitions(${CMAKE_PROJECT_NAME}engine PUBLIC -DENABLE_LOGGING)

  # add spdlog for logging
  if(USE_SPDLOG_LOGGING)
    target_compile_definitions(${CMAKE_PROJECT_NAME}engine PUBLIC -DUSE_SPDLOG_LOGGING)
    target_link_libraries(${CMAKE_PROJECT_NAME}engine PUBLIC CONAN_PKG::spdlog CONAN_PKG::fmt)
  endif()
endif()

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME}engine PUBLIC Threads::Threads)
