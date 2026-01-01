add_library(util
    arena.cpp
    bitmap.cpp
    hash.cpp
    simd.cpp
    stopwatch.cpp
    string_pool.cpp
)

target_link_libraries(util
    PUBLIC
        project_options
)