add_library(aggregate
    aggregate.cpp
)

target_link_libraries(aggregate
    PUBLIC
        project_options
        util
        execution_vector
        execution_expressions
    PRIVATE
        execution_memory
)