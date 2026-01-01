add_library(execution_memory
    query_arena.cpp
    spill_manager.cpp
)

target_link_libraries(execution_memory
    PUBLIC
        project_options
        util
        io
)