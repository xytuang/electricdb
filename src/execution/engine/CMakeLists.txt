add_library(execution_engine
    operator.cpp
    pipeline_builder.cpp
    pipeline.cpp
    scheduler.cpp
)

target_link_libraries(execution_engine
    PUBLIC
        project_options
        util
        execution_vector
        execution_memory
        execution_expressions
        execution_operators
)
