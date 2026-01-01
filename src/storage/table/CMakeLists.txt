add_library(storage_table
    partition.cpp
    schema.cpp
    table.cpp
)

target_link_libraries(storage_table
    PUBLIC
        project_options
)