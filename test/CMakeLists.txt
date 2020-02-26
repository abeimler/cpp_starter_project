# automatically enable catch2 to generate ctest targets
if(CONAN_CATCH2_ROOT_DEBUG)
  include(${CONAN_CATCH2_ROOT_DEBUG}/lib/cmake/Catch2/Catch.cmake)
else()
  include(${CONAN_CATCH2_ROOT}/lib/cmake/Catch2/Catch.cmake)
endif()

add_library(catch_main STATIC ${CMAKE_CURRENT_SOURCE_DIR}/catch_main.cpp)
target_link_libraries(catch_main PUBLIC CONAN_PKG::catch2)

add_subdirectory(constexpr_tests)
add_subdirectory(tests)

if(BUILD_INTEGRATION_TESTS)
  message(
    "Building Integration Tests. Be sure to check out test/integration_tests for integration testing"
  )
  add_subdirectory(integrartion_tests)
endif()