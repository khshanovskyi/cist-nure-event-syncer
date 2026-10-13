#pragma once

#include <cstdint>
#include <filesystem>
#include <string>

namespace bot {

// Everything tg-bot reads from the environment, loaded once at startup (implementation-plan.md §8.3).
struct Config {
    std::string syncerUrl;                         // SCHEDULER_APP_URL, e.g. http://cist-syncer:8080
    std::string botToken;                          // TG_BOT_TOKEN
    std::int64_t ownerChatId = 0;                  // TG_OWNER_CHAT_ID; chat ids don't fit in 32 bits
    std::filesystem::path settingsPath = "/data/settings.json";

    // Throws std::runtime_error naming the first missing or invalid variable.
    static Config fromEnv();
};

}  // namespace bot
