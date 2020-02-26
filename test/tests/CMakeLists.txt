set(${CMAKE_PROJECT_NAME}_TEST_HEADERS "")
set(${CMAKE_PROJECT_NAME}_TEST_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_TEST_HEADERS ")
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
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_TEST_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           if "catch_main.cpp" in os.path.relpath(src, path): continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND ${CMAKE_PROJECT_NAME}_TEST_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Test Header Files"
  FILES ${${CMAKE_PROJECT_NAME}_TEST_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Test Source Files"
  FILES ${${CMAKE_PROJECT_NAME}_TEST_SOURCE})

add_executable(${CMAKE_PROJECT_NAME}-test)
target_link_libraries(${CMAKE_PROJECT_NAME}-test project_warnings project_options catch_main)
target_sources(${CMAKE_PROJECT_NAME}-test PRIVATE ${${CMAKE_PROJECT_NAME}_TEST_SOURCE}
                                                  ${${CMAKE_PROJECT_NAME}_TEST_HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME}-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME}-test PRIVATE ${PROJECT_BINARY_DIR}/include)

# TODO: add libs
target_link_libraries(${CMAKE_PROJECT_NAME}-test ${CMAKE_PROJECT_NAME}::core)
target_link_libraries(${CMAKE_PROJECT_NAME}-test ${CMAKE_PROJECT_NAME}::bitsery)
target_link_libraries(${CMAKE_PROJECT_NAME}-test Bitsery::bitsery)
target_link_libraries(${CMAKE_PROJECT_NAME}-test ${CMAKE_PROJECT_NAME}::json)
target_link_libraries(${CMAKE_PROJECT_NAME}-test nlohmann_json::nlohmann_json)

target_compile_definitions(${CMAKE_PROJECT_NAME}-test PUBLIC -DTESTING)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME}-test Threads::Threads)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to
# whatever you want, or use different for different binaries
catch_discover_tests(
  ${CMAKE_PROJECT_NAME}-test
  TEST_PREFIX
  "unittests."
  EXTRA_ARGS
  -s
  --reporter=xml
  --out=tests.xml)
