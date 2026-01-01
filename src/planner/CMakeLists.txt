add_subdirectory(logical)
add_subdirectory(physical)

add_library(planner
    planner.cpp
)

target_link_libraries(planner
    PUBLIC
        project_options
        catalog
        planner_logical
        planner_physical
)
