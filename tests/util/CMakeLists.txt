add_executable(util_test
    arena_test.cpp
)

target_link_libraries(util_test
    PRIVATE
        util
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(util_test)