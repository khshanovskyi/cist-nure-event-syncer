#include "Config.hpp"

#include <charconv>
#include <stdexcept>

#include "common/Env.hpp"

namespace syncer {
namespace {

int parsePort(const std::string& text) {
    int port = 0;
    const auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), port);
    if (error != std::errc{} || end != text.data() + text.size() || port < 1 || port > 65535) {
        throw std::runtime_error("PORT must be a number between 1 and 65535, got '" + text + "'");
    }
    return port;
}

}  // namespace

Config Config::fromEnv() {
    Config config;
    config.port = parsePort(common::envOr("PORT", "8080"));
    config.databaseUrl = common::requireEnv("DATABASE_URL");
    config.nureGroup = common::requireEnv("NURE_GROUP");
    config.calendarId = common::requireEnv("GOOG_CALENDAR_ID");
    config.googleKeyFile = common::requireEnv("GOOG_CAL_ROBOT_KEY");   // a path, never the key itself (case 30)
    return config;
}

}  // namespace syncer
