add_executable(example-tests example.t.cpp)

target_link_libraries(example-tests PRIVATE libisaac)

add_test(example-test example-test)