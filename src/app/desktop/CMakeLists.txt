# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("set(APP_DESKTOP_${CMAKE_PROJECT_NAME}_HEADERS ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
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
#       cog.outl("set(APP_DESKTOP_${CMAKE_PROJECT_NAME}_SOURCE ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
set(APP_DESKTOP_${CMAKE_PROJECT_NAME}_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Desktop App Header Files"
  FILES ${APP_DESKTOP_${CMAKE_PROJECT_NAME}_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Desktop App Main Source Files"
  FILES ${APP_DESKTOP_${CMAKE_PROJECT_NAME}_SOURCE})

add_executable(${CMAKE_PROJECT_NAME}-desktop)
target_link_libraries(${CMAKE_PROJECT_NAME}-desktop project_warnings project_options)
target_sources(${CMAKE_PROJECT_NAME}-desktop PRIVATE ${APP_DESKTOP_${CMAKE_PROJECT_NAME}_SOURCE}
                                                     ${APP_DESKTOP_${CMAKE_PROJECT_NAME}_HEADERS})
                                                     
target_include_directories(${CMAKE_PROJECT_NAME}-desktop PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# TODO:add libs
target_link_libraries(${CMAKE_PROJECT_NAME}-desktop ${CMAKE_PROJECT_NAME}::engine)
target_link_libraries(${CMAKE_PROJECT_NAME}-desktop raylib)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME}-desktop Threads::Threads)
