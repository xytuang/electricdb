add_library(sort
    sort.cpp
)

target_link_libraries(sort
    PUBLIC
        project_options
        util
        execution_vector
        execution_expressions
    PRIVATE
        execution_memory
)