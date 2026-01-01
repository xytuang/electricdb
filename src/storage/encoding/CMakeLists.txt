add_library(storage_encoding
    delta.cpp
    dictionary.cpp
    encoding.cpp
    for.cpp
    plain.cpp
    rle.cpp
)

target_link_libraries(storage_encoding
    PUBLIC
        project_options
)