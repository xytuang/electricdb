add_library(catalog
    catalog.cpp
    commit_log.cpp
    schema_entry.cpp
    snapshot.cpp
    statistics.cpp
)

target_link_libraries(catalog
    PUBLIC
        project_options
        storage
        util
)