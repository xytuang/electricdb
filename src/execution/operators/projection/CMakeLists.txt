add_library(projection
    projection.cpp
)

target_link_libraries(projection
    PUBLIC
        project_options
        util
        execution_vector
        execution_expressions
    PRIVATE
        execution_memory
)