cmake_minimum_required(VERSION 4.3)
project(cist-nure-event-syncer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)              # -std=c++20, not -std=gnu++20

option(BUILD_SYNCER "Build the cist-syncer service" ON)
option(BUILD_BOT "Build the tg-bot service" ON)
option(ENABLE_SANITIZERS "Build with AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

include(CTest)                             # defines BUILD_TESTING (ON by default) and enables `ctest`
include(cmake/ProjectOptions.cmake)

add_subdirectory(libs/common)
if(BUILD_SYNCER)
    add_subdirectory(services/cist-syncer)
endif()
if(BUILD_BOT)
    add_subdirectory(services/tg-bot)
endif()
