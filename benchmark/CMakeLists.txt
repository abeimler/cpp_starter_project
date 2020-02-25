add_library(benchpress_main STATIC ${CMAKE_CURRENT_SOURCE_DIR}/benchpress_main.cpp)
target_link_libraries(benchpress_main PUBLIC benchpress)

add_subdirectory(benchmarks)
