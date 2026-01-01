add_library(execution_vector
    nullmask.cpp
    selection_vector.cpp
    vector.cpp
)

target_link_libraries(execution_vector
    PUBLIC
        project_options
        util
)
