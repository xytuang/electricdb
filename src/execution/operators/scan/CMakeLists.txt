add_library(scan
    scan.cpp
)

target_link_libraries(scan
    PUBLIC
        project_options
        util
        execution_vector
        execution_expressions
    PRIVATE
        execution_memory
)