add_library(runtime
    cancellation.cpp
    metrics.cpp
    query_context.cpp
    query_state.cpp
    result_set.cpp
)

target_link_libraries(runtime
    PUBLIC
        project_options
)