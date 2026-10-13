#include <exception>

#include <spdlog/spdlog.h>

#include "Config.hpp"
#include "common/Logging.hpp"

// Step 1 skeleton (implementation-plan.md §11): load the config, log it and stop.
// The Telegram long poll, scheduler and sync workflow are wired in here from Step 7 on (§8.10).
int main() {
    common::initLogging("tg-bot");
    try {
        const auto config = bot::Config::fromEnv();
        // botToken is not logged: anyone holding it controls the bot
        spdlog::info("hello from tg-bot: syncer at {}, owner chat {}, settings in {}",
                     config.syncerUrl, config.ownerChatId, config.settingsPath.string());
        return 0;
    } catch (const std::exception& e) {
        spdlog::critical("startup failed: {}", e.what());
        return 1;
    }
}
