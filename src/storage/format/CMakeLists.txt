add_library(storage_format
    column_file.cpp
    file_header.cpp
    metadata.cpp
)

target_link_libraries(storage_format
    PUBLIC
        project_options
)