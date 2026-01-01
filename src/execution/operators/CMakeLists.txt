add_subdirectory(aggregate)
add_subdirectory(filter)
add_subdirectory(join)
add_subdirectory(out)
add_subdirectory(projection)
add_subdirectory(scan)
add_subdirectory(sort)

add_library(execution_operators INTERFACE)

target_link_libraries(execution_operators
    INTERFACE
        project_options
        util
        execution_vector
        execution_expressions
        execution_memory
        scan
        filter
        aggregate
        join
        out
        projection
        sort
)