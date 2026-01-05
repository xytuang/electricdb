# Tests are only built in Debug

if (NOT CMAKE_CONFIGURATION_TYPES)
    # Single-config
    if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
        message(STATUS "Skipping tests (not Debug build)")
        return()
    endif()
endif()

add_subdirectory(util)