add_executable(execution_expressions_test
    leaf_expression_test.cpp
    unary_expression_test.cpp
    binary_expression_test.cpp
)

target_link_libraries(execution_expressions_test
    PRIVATE
        execution_expressions
        execution_vector
        util
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(execution_expressions_test)