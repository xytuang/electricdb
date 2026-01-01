add_subdirectory(column)
add_subdirectory(encoding)
add_subdirectory(format)
add_subdirectory(gc)
add_subdirectory(table)

add_library(storage INTERFACE)

target_link_libraries(storage
    INTERFACE
        project_options
        io
        util
        storage_column
        storage_encoding
        storage_format
        storage_gc
        storage_table
)
