add_library(sql_binder
    binder.cpp
    bound_expr.cpp
)

target_link_libraries(sql_binder
    PUBLIC
        project_options
)