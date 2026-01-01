add_library(filter
    filter.cpp
)

target_link_libraries(filter
    PUBLIC
        project_options
        util
        execution_vector
        execution_expressions
    PRIVATE
        execution_memory
)