# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h??').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("set(${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_HEADERS ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
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
#       cog.outl("set(${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_SOURCE ")    ###< you need to CHANGE this line (string) with your sourcecode-list cmake variable name
#       for src in files:
#           if "skeleton" in src: continue
#           if "catch_main.cpp" in os.path.relpath(src, path): continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
set(${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/constexpr_tests.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "constexpr Test Header Files"
  FILES ${${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "constexpr Test Source Files"
  FILES ${${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_SOURCE})

add_executable(${CMAKE_PROJECT_NAME}-constexpr-tests)
target_link_libraries(${CMAKE_PROJECT_NAME}-constexpr-tests project_warnings project_options catch_main)
target_sources(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE ${${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_SOURCE}
                                                             ${${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE ${PROJECT_BINARY_DIR}/include)

# TODO: add libs
target_link_libraries(${CMAKE_PROJECT_NAME}-constexpr-tests ${CMAKE_PROJECT_NAME}::core)

# automatically discover tests that are defined in catch based test files you can modify the unittests. TEST_PREFIX to
# whatever you want, or use different for different binaries
catch_discover_tests(
  ${CMAKE_PROJECT_NAME}-constexpr-tests
  TEST_PREFIX
  "constexpr."
  EXTRA_ARGS
  -s
  --reporter=xml
  --out=constexpr.xml)

# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when
# things go wrong with the constexpr testing
add_executable(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests)
target_link_libraries(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests project_warnings project_options catch_main)
target_sources(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE ${${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_SOURCE}
                                                                     ${${CMAKE_PROJECT_NAME}_CONSTEXPR_TEST_HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests CONAN_PKG::spdlog)
target_link_libraries(${CMAKE_PROJECT_NAME}-relaxed-constexpr-tests CONAN_PKG::fmt)

target_compile_definitions(${CMAKE_PROJECT_NAME}-constexpr-tests PUBLIC -DCONSTEXPR_TESTING)
target_compile_definitions(${CMAKE_PROJECT_NAME}-constexpr-tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

catch_discover_tests(
  ${CMAKE_PROJECT_NAME}-constexpr-tests
  TEST_PREFIX
  "relaxed_constexpr."
  EXTRA_ARGS
  -s
  --reporter=xml
  --out=relaxed_constexpr.xml)
