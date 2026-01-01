add_library(io
    file.cpp
    directory.cpp
    fsync.cpp
    mmap_file.cpp
    prefetch.cpp
)

target_link_libraries(io
    PUBLIC
        project_options
        util
)