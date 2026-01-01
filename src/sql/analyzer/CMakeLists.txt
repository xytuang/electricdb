add_library(sql_analyzer
    semantic_checks.cpp
)

target_link_libraries(sql_analyzer
    PUBLIC
        project_options
)