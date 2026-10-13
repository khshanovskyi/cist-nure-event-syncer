find_package(cpr CONFIG REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
find_package(Threads REQUIRED)

# tgbot-cpp: check build/debug/vcpkg_installed/<triplet>/share/tgbot-cpp/usage and follow it.
# The plain find_path/find_library form below works with the vcpkg port. If the linker reports
# missing Boost or curl symbols, add what the usage file lists.
find_path(TGBOT_INCLUDE_DIR tgbot/tgbot.h REQUIRED)
find_library(TGBOT_LIBRARY TgBot REQUIRED)

# Add each new .cpp here as you write it; the full list is in implementation-plan.md §4.6.
add_library(bot_core STATIC
    src/Config.cpp
)
target_include_directories(bot_core PUBLIC src ${TGBOT_INCLUDE_DIR})
target_link_libraries(bot_core PUBLIC
    cistsync::common
    cpr::cpr
    ${TGBOT_LIBRARY}
    OpenSSL::SSL
    OpenSSL::Crypto
    ZLIB::ZLIB
    Threads::Threads
)
cistsync_set_warnings(bot_core)

add_executable(tg-bot src/main.cpp)
target_link_libraries(tg-bot PRIVATE bot_core)
cistsync_set_warnings(tg-bot)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
