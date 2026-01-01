add_library(storage_gc
    garbage_collector.cpp
)

target_link_libraries(storage_gc
    PUBLIC
        project_options
)