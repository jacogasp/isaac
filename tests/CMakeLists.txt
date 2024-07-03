add_executable(physics-tests physics.t.cpp)

target_link_libraries(physics-tests PRIVATE isaac)

add_test(physics-test physics-test)

find_package(benchmark REQUIRED)
if (benchmark_FOUND)
    add_executable(bench benchmark.cpp)
    target_link_libraries(bench benchmark::benchmark isaac)
endif()
