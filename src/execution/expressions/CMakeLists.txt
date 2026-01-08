add_library(execution_expressions
    codegen.cpp
    eval.cpp
    leaf_expression.cpp
    unary_expression.cpp
    binary_expression.cpp
)

target_link_libraries(execution_expressions
    PUBLIC
        project_options
        util
        execution_vector
)