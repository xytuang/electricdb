add_subdirectory(parser)
add_subdirectory(analyzer)
add_subdirectory(binder)

add_library(sql
    sql_frontend.cpp
)

target_link_libraries(sql
    PUBLIC
        project_options
        catalog
        planner
    PRIVATE
        sql_parser
        sql_analyzer
        sql_binder
)
