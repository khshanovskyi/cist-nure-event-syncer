#pragma once

#include <string>

namespace common {

// Makes a colored stdout logger named after the service the default for spdlog::info(...) and friends.
// The level comes from LOG_LEVEL (trace, debug, info, warn, error, critical, off); the default is info.
// Call once, at the top of main().
void initLogging(const std::string& serviceName);

}  // namespace common
