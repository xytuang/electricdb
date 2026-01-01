cmake_minimum_required(VERSION 3.14)
project(ElectricDB LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---------------------------------
# Options
# ---------------------------------
option(ENABLE_LOGGING "Enable Logging" ON)

option(ENABLE_CLANG_TIDY "Enable clang-tidy analysis" ON)

# ---------------------------------
# Build configurations
# ---------------------------------

# Single-config generators (Make, Ninja)
if (NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING
        "Choose the build type: Debug or Release"
        FORCE
    )
endif()

# Multi-config generators (Xcode, VS, Ninja Multi-Config)
if (CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES
        Debug
        Release
        CACHE STRING "" FORCE
    )
endif()

# ---------------------------------
# Dependencies
# ---------------------------------
if (ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if (NOT CLANG_TIDY_EXE)
        message(FATAL_ERROR "clang-tidy requested but not found")
    endif()
endif()

if (ENABLE_CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY
        ${CLANG_TIDY_EXE};
        --warnings-as-errors=*;
        --header-filter=^${PROJECT_SOURCE_DIR}/src/
    )
endif()

find_program(CLANG_FORMAT_EXE NAMES clang-format)

if (CLANG_FORMAT_EXE)
    file(GLOB_RECURSE ALL_CXX_FILES
        ${PROJECT_SOURCE_DIR}/src/*.cpp
        ${PROJECT_SOURCE_DIR}/src/*.h
        ${PROJECT_SOURCE_DIR}/src/*.hpp
    )

    add_custom_target(format
        COMMAND ${CLANG_FORMAT_EXE}
        -i
        -style=file
        ${ALL_CXX_FILES}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Running clang-format on source files"
    )
endif()
# ---------------------------------
# Common interface target
# ---------------------------------
add_library(project_options INTERFACE)

# Compile definitions
target_compile_definitions(project_options
    INTERFACE
        $<$<CONFIG:Debug>:DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<BOOL:${ENABLE_LOGGING}>:LOGGING_ENABLED>
)

# Compile options
target_compile_options(project_options
    INTERFACE
        $<$<CONFIG:Debug>:-O0 -g>
        $<$<CONFIG:Release>:-O2>
)

# Sanitizers in Debug only (GCC / Clang)
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(project_options
        INTERFACE
            $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
    target_link_options(project_options
        INTERFACE
            $<$<CONFIG:Debug>:-fsanitize=address,undefined>
    )
    target_compile_options(project_options
        INTERFACE
            -Wall
            -Wextra
            -Wpedantic
    )
elseif (MSVC)
    target_compile_options(project_options
        INTERFACE
            /W4
    )
endif()

# Common include path
target_include_directories(project_options
    INTERFACE ${PROJECT_SOURCE_DIR}/src/include
)

# ---------------------------------
# third party/external dependencies
# ---------------------------------
add_subdirectory(third_party)

# ---------------------------------
# Main project
# ---------------------------------
add_subdirectory(src)

# ---------------------------------
# Tests
# Compilation of test into binary is decided by tests/CMakeLists.txt
# ---------------------------------
enable_testing()
add_subdirectory(tests)