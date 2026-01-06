add_executable(execution_vector_test
    nullmask_test.cpp
    selection_vector_test.cpp
    vector_test.cpp
)

target_link_libraries(execution_vector_test
    PRIVATE
        execution_vector
        util
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(execution_vector_test)