#include "Config.hpp"

#include <charconv>
#include <stdexcept>

#include "common/Env.hpp"

namespace bot {
namespace {

std::int64_t parseChatId(const std::string& text) {
    std::int64_t id = 0;
    const auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), id);
    if (error != std::errc{} || end != text.data() + text.size() || id == 0) {
        throw std::runtime_error("TG_OWNER_CHAT_ID must be a numeric chat id, got '" + text + "'");
    }
    return id;
}

}  // namespace

Config Config::fromEnv() {
    Config config;
    config.syncerUrl = common::requireEnv("SCHEDULER_APP_URL");
    config.botToken = common::requireEnv("TG_BOT_TOKEN");
    config.ownerChatId = parseChatId(common::requireEnv("TG_OWNER_CHAT_ID"));
    config.settingsPath = common::envOr("SETTINGS_PATH", config.settingsPath.string());
    return config;
}

}  // namespace bot
