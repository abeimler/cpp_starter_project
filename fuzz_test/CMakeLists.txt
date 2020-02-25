# A fuzz test runs until it finds an error. This particular one is going to rely on libFuzzer.
#

set(${CMAKE_PROJECT_NAME}_FUZZ_TEST_HEADERS "")
set(${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_FUZZ_TEST_HEADERS ")
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
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           if "catch_main.cpp" in os.path.relpath(src, path): continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND ${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/fuzz_tester.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Test Header Files"
  FILES ${${CMAKE_PROJECT_NAME}_FUZZ_TEST_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Test Source Files"
  FILES ${${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE})

add_executable(${CMAKE_PROJECT_NAME}-fuzz-test)
target_sources(${CMAKE_PROJECT_NAME}-fuzz-test PRIVATE ${${CMAKE_PROJECT_NAME}_FUZZ_TEST_SOURCE}
                                                       ${${CMAKE_PROJECT_NAME}_FUZZ_TEST_HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME}-fuzz-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME}-fuzz-test PRIVATE project_options project_warnings CONAN_PKG::fmt -coverage
                                                              -fsanitize=fuzzer,undefined,address)
target_compile_options(${CMAKE_PROJECT_NAME}-fuzz-test PRIVATE -fsanitize=fuzzer,undefined,address)

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME fuzz_tester_run COMMAND ${CMAKE_PROJECT_NAME}-fuzz-test -max_total_time=${FUZZ_RUNTIME})
