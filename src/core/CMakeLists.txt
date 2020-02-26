set(${CMAKE_PROJECT_NAME}_HEADERS "")
set(${CMAKE_PROJECT_NAME}_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_HEADERS ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND ${CMAKE_PROJECT_NAME}_HEADERS 
    ${CMAKE_CURRENT_SOURCE_DIR}/Bar.h 
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
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND ${CMAKE_PROJECT_NAME}_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/Bar.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Core Header Files"
  FILES ${${CMAKE_PROJECT_NAME}_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Core Source Files"
  FILES ${${CMAKE_PROJECT_NAME}_SOURCE})

add_library(${CMAKE_PROJECT_NAME} STATIC)
add_library(${CMAKE_PROJECT_NAME}::core ALIAS ${CMAKE_PROJECT_NAME})
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE project_warnings project_options)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${${CMAKE_PROJECT_NAME}_SOURCE} ${${CMAKE_PROJECT_NAME}_HEADERS})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PROJECT_BINARY_DIR}/include)

# @TODO: add libs
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC CONAN_PKG::date)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC CONAN_PKG::magic_enum)
