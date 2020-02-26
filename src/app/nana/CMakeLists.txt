include(ExternalProject)
ExternalProject_Add(
  Nana
  GIT_REPOSITORY https://github.com/cnjinhao/nana.git
  GIT_TAG v1.6.2
  CMAKE_CACHE_ARGS "-DNANA_CMAKE_SHARED_LIB:BOOL=TRUE"
  INSTALL_COMMAND "")

# ExternalProject_Get_Property(Nana NANA_INCLUDE_DIR)
ExternalProject_Get_Property(Nana SOURCE_DIR BINARY_DIR)

set(APP_NANA_HEADERS "")
set(APP_NANA_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND APP_NANA_HEADERS ")
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
#       cog.outl("list(APPEND APP_NANA_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND APP_NANA_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Nana Header Files"
  FILES ${APP_NANA_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Nana Source Files"
  FILES ${APP_NANA_SOURCE})

add_executable(test_nana)
target_link_libraries(test_nana PRIVATE project_warnings project_options)
target_sources(test_nana PRIVATE ${APP_NANA_SOURCE} ${APP_NANA_HEADERS})

target_include_directories(test_nana PRIVATE ${SOURCE_DIR}/include)
add_dependencies(test_nana Nana)
target_link_libraries(test_nana PRIVATE ${BINARY_DIR}/libnana.so ${NANA_LINKS})
