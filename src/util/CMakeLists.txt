add_library(util
    arena.cpp
    hash.cpp
    simd.cpp
    stopwatch.cpp
)

target_link_libraries(util
    PUBLIC
        project_options
)