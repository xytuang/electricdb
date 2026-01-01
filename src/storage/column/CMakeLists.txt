add_library(storage_column
    chunk.cpp
    column_reader.cpp
    column_writer.cpp
    zone_map.cpp
)

target_link_libraries(storage_column
    PUBLIC
        project_options
)