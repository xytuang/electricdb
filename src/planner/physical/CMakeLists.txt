add_library(planner_physical
    cost_model.cpp
    physical_plan.cpp
    rewrite.cpp
)

target_link_libraries(planner_physical
    PUBLIC
        project_options
        catalog
        util
)