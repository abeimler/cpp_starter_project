set(PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_HEADERS "")
set(PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_HEADERS ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/units.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/magic_enum.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/etl/array.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/etl/cstring.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/etl/vector.h 
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
#       cog.outl("list(APPEND PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "JSON Persistence Lib Header Files"
  FILES ${PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "JSON Persistence Lib Source Files"
  FILES ${PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_SOURCE})

add_library(${CMAKE_PROJECT_NAME}_json INTERFACE)
# target_link_libraries(${CMAKE_PROJECT_NAME}_json INTERFACE project_warnings project_options)
target_sources(${CMAKE_PROJECT_NAME}_json INTERFACE ${PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_SOURCE}
                                                    ${PERSISTENCE_JSON${CMAKE_PROJECT_NAME}_HEADERS})
add_library(${CMAKE_PROJECT_NAME}::json ALIAS ${CMAKE_PROJECT_NAME}_json)

target_include_directories(${CMAKE_PROJECT_NAME}_json INTERFACE ${PROJECT_SOURCE_DIR}/src/persistence)
target_include_directories(${CMAKE_PROJECT_NAME}_json INTERFACE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}_json INTERFACE ${PROJECT_BINARY_DIR}/include)

# todo: add libs
target_link_libraries(${CMAKE_PROJECT_NAME}_json INTERFACE nlohmann_json::nlohmann_json)
target_link_libraries(${CMAKE_PROJECT_NAME}_json INTERFACE ${CMAKE_PROJECT_NAME}::core)
