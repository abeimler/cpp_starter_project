find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED IMPORTED_TARGET gtkmm-3.0)

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("set(APP_GTKMM_HEADERS ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
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
#       cog.outl("set(APP_GTKMM_SOURCE ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
set(APP_GTKMM_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/hello_world.cpp 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "gtkmm Header Files"
  FILES ${APP_GTKMM_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "gtkmm Source Files"
  FILES ${APP_GTKMM_SOURCE})

add_executable(test_gtkmm)
target_link_libraries(test_gtkmm PRIVATE project_warnings project_options)
target_sources(test_gtkmm PRIVATE ${APP_GTKMM_SOURCE} ${APP_GTKMM_HEADERS})

target_link_libraries(test_gtkmm PRIVATE PkgConfig::GTKMM)
