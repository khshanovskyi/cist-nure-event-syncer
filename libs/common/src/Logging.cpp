#include "common/Logging.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include "common/Env.hpp"

namespace common {

void initLogging(const std::string& serviceName) {
    spdlog::set_default_logger(spdlog::stdout_color_mt(serviceName));
    spdlog::set_pattern("%Y-%m-%d %H:%M:%S.%e %^%-5l%$ [%n] %v");

    const std::string levelName = envOr("LOG_LEVEL", "info");
    auto level = spdlog::level::from_str(levelName);
    // from_str returns `off` for unknown names, which would silently hide every log line
    if (level == spdlog::level::off && levelName != "off") {
        level = spdlog::level::info;
        spdlog::warn("unknown LOG_LEVEL '{}', using info", levelName);
    }
    spdlog::set_level(level);
}

}  // namespace common
