set(${CMAKE_PROJECT_NAME}_BENCHMARK_HEADERS "")
set(${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE "")

# cmake-format: off
# [[[cog
#    import os, cog, glob
#    path, file = os.path.split(cog.inFile)
#    filepattern = os.path.join(path, '**/*.h').lstrip('./')
#    files = glob.glob(filepattern, recursive=True)
#    if files:
#       cog.outl("## GENERATED CODE WITH cogapp")
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_BENCHMARK_HEADERS ")
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
#       cog.outl("list(APPEND ${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE ")
#       for src in files:
#           if "skeleton" in src: continue
#           if "benchpress_main.cpp" in os.path.relpath(src, path): continue
#           cog.outl("    ${CMAKE_CURRENT_SOURCE_DIR}/%s " % os.path.relpath(src, path))
#       cog.outl(")")
# ]]]
## GENERATED CODE WITH cogapp
list(APPEND ${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE 
    ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp 
)
# [[[end]]]
# cmake-format: on

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Benchmark Header Files"
  FILES ${${CMAKE_PROJECT_NAME}_BENCHMARK_HEADERS})
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Benchmark Source Files"
  FILES ${${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE})

add_executable(${CMAKE_PROJECT_NAME}-benchmark)
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark project_warnings project_options benchpress_main)
target_sources(${CMAKE_PROJECT_NAME}-benchmark PRIVATE ${${CMAKE_PROJECT_NAME}_BENCHMARK_SOURCE}
                                                       ${${CMAKE_PROJECT_NAME}_BENCHMARK_HEADERS})
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PUBLIC ${PROJECT_SOURCE_DIR}/app)
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PUBLIC ${PROJECT_SOURCE_DIR}/src)
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PUBLIC ${PROJECT_SOURCE_DIR}/src/persistence)
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${CMAKE_PROJECT_NAME}-benchmark PRIVATE ${PROJECT_BINARY_DIR}/include)

# todo: add libs
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark ${CMAKE_PROJECT_NAME}::core)
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark ${CMAKE_PROJECT_NAME}::bitsery)
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark Bitsery::bitsery)
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark ${CMAKE_PROJECT_NAME}::json)
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark nlohmann_json::nlohmann_json)
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark ${CMAKE_PROJECT_NAME}::engine)

target_compile_definitions(${CMAKE_PROJECT_NAME}-benchmark PUBLIC -DBENCHMARKING)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${CMAKE_PROJECT_NAME}-benchmark Threads::Threads)
