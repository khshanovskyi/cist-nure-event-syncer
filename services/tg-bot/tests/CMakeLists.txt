find_package(GTest CONFIG REQUIRED)

# Add each new test file here as you write it.
add_executable(bot_tests
    LibrariesSmokeTest.cpp
)
target_link_libraries(bot_tests PRIVATE bot_core GTest::gtest_main)
cistsync_set_warnings(bot_tests)

include(GoogleTest)
gtest_discover_tests(bot_tests)        # each TEST() shows up separately in ctest and in CLion
