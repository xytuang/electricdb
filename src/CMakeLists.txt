add_subdirectory(util)
add_subdirectory(io)
add_subdirectory(storage)
add_subdirectory(catalog)
add_subdirectory(sql)
add_subdirectory(planner)
add_subdirectory(execution)
add_subdirectory(runtime)

add_executable(electricdb main/cli.cpp)

target_link_libraries(electricdb
    PRIVATE
        runtime
        sql
)