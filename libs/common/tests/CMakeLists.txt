find_package(GTest CONFIG REQUIRED)

add_executable(common_tests
    EnvTest.cpp
)
target_link_libraries(common_tests PRIVATE cistsync::common GTest::gtest_main)
cistsync_set_warnings(common_tests)

include(GoogleTest)
gtest_discover_tests(common_tests)     # each TEST() shows up separately in ctest and in CLion
