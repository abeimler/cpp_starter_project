# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("set(PERSISTENCE_BINARY${CMAKE_PROJECT_NAME}_HEADERS ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
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
#       cog.outl("set(PERSISTENCE_BINARY${CMAKE_PROJECT_NAME}_SOURCE ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Binary Persistence Lib Header Files"
  FILES ${PERSISTENCE_BINARY${CMAKE_PROJECT_NAME}_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Binary Persistence Lib Source Files"
  FILES ${PERSISTENCE_BINARY${CMAKE_PROJECT_NAME}_SOURCE})

add_library(${CMAKE_PROJECT_NAME}_bitsery INTERFACE)
add_library(${CMAKE_PROJECT_NAME}::bitsery ALIAS ${CMAKE_PROJECT_NAME}_bitsery)
# target_link_libraries(${CMAKE_PROJECT_NAME}_bitsery INTERFACE project_warnings project_options)
target_sources(${CMAKE_PROJECT_NAME}_bitsery INTERFACE ${PERSISTENCE_BINARY${CMAKE_PROJECT_NAME}_SOURCE}
                                                       ${PERSISTENCE_BINARY${CMAKE_PROJECT_NAME}_HEADERS})

target_include_directories(${CMAKE_PROJECT_NAME}_bitsery INTERFACE ${PROJECT_SOURCE_DIR}/src/persistence)

# todo: add libs
target_link_libraries(${CMAKE_PROJECT_NAME}_bitsery INTERFACE Bitsery::bitsery)
target_link_libraries(${CMAKE_PROJECT_NAME}_bitsery INTERFACE ${CMAKE_PROJECT_NAME}::core)
