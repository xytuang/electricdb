add_library(execution_expressions
    codegen.cpp
    eval.cpp
    expression.cpp
)

target_link_libraries(execution_expressions
    PUBLIC
        project_options
        util
        execution_vector
)