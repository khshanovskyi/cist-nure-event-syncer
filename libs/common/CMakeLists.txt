find_package(nlohmann_json CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

# Add each new .cpp here as you write it; the full list is in implementation-plan.md §4.4.
add_library(common STATIC
    src/Env.cpp
    src/Logging.cpp
)
add_library(cistsync::common ALIAS common)      # namespaced alias, a typo becomes a configure error
target_include_directories(common PUBLIC include)
target_link_libraries(common PUBLIC nlohmann_json::nlohmann_json spdlog::spdlog)
cistsync_set_warnings(common)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
