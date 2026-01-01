add_library(planner_logical
    logical_plan.cpp
    nodes.cpp
    rules.cpp
)

target_link_libraries(planner_logical
    PUBLIC
        project_options
        catalog
        util
)
