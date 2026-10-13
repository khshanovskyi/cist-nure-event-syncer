find_package(GTest CONFIG REQUIRED)

# Add each new test file here; the planned list is in implementation-plan.md §4.7.
add_executable(syncer_tests
    LibrariesSmokeTest.cpp
)
target_link_libraries(syncer_tests PRIVATE syncer_core GTest::gtest_main)
target_compile_definitions(syncer_tests PRIVATE FIXTURES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/fixtures")
cistsync_set_warnings(syncer_tests)

include(GoogleTest)
gtest_discover_tests(syncer_tests)     # each TEST() shows up separately in ctest and in CLion
