add_library(sql_parser
    lexer.cpp
    parser.cpp
    ast.cpp
)

target_link_libraries(sql_parser
    PUBLIC
        project_options
)