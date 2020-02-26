find_package(Qt5Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)

set(APP_QT_HEADERS "")
set(APP_QT_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND APP_QT_HEADERS ")
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
#    filepattern = os.path.join(path, '**/*.c*').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND APP_QT_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND APP_QT_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/qtMain.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/HelloQt.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Qt Header Files"
  FILES ${APP_QT_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Qt Source Files"
  FILES ${APP_QT_SOURCE})

add_executable(helloQt)
target_link_libraries(helloQt PRIVATE project_warnings project_options)
target_sources(helloQt PRIVATE ${APP_QT_SOURCE} ${APP_QT_HEADERS})

#set_target_properties(helloQt PROPERTIES CMAKE_AUTOMOC ON)
target_link_libraries(helloQt PRIVATE Qt5::Widgets)
target_compile_features(helloQt PUBLIC cxx_nullptr cxx_lambdas)
