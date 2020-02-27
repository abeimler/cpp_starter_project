# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("set(APP_INTRO_HEADERS ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
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
#       cog.outl("set(APP_INTRO_SOURCE ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
set(APP_INTRO_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Intro Header Files"
  FILES ${APP_INTRO_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Intro Source Files"
  FILES ${APP_INTRO_SOURCE})

add_library(intro)
target_link_libraries(intro PRIVATE project_warnings project_options)
target_sources(intro PRIVATE ${APP_INTRO_SOURCE} ${APP_INTRO_HEADERS})

target_link_libraries(intro PRIVATE CONAN_PKG::docopt.cpp CONAN_PKG::fmt CONAN_PKG::spdlog)
