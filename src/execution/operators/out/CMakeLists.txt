add_library(out
    out.cpp
)

target_link_libraries(out
    PUBLIC
        project_options
        util
        execution_vector
        execution_expressions
    PRIVATE
        execution_memory
)