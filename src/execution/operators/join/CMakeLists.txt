add_library(join
    join.cpp
)

target_link_libraries(join
    PUBLIC
        project_options
        util
        execution_vector
        execution_expressions
    PRIVATE
        execution_memory
)