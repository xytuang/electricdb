add_subdirectory(vector)
add_subdirectory(memory)
add_subdirectory(expressions)
add_subdirectory(engine)
add_subdirectory(operators)

add_library(execution INTERFACE)

target_link_libraries(execution
    INTERFACE
        project_options
        util
        planner_physical
        execution_engine
        execution_operators
        execution_vector
        execution_expressions
        execution_memory
)
