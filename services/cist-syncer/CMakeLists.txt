find_package(cpr CONFIG REQUIRED)
find_package(httplib CONFIG REQUIRED)
find_package(jwt-cpp CONFIG REQUIRED)
find_package(libpqxx CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)

# Add each new .cpp here as you write it; the full list is in implementation-plan.md §4.5.
add_library(syncer_core STATIC
    src/Config.cpp
)
target_include_directories(syncer_core PUBLIC src)       # #include "cist/Csv.hpp"
target_link_libraries(syncer_core PUBLIC
    cistsync::common
    cpr::cpr
    httplib::httplib
    jwt-cpp::jwt-cpp
    libpqxx::pqxx
    OpenSSL::Crypto
)
cistsync_set_warnings(syncer_core)

add_executable(cist-syncer src/main.cpp)
target_link_libraries(cist-syncer PRIVATE syncer_core)
cistsync_set_warnings(cist-syncer)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
