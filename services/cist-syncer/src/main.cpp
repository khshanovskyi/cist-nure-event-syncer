#include <exception>

#include <spdlog/spdlog.h>

#include "Config.hpp"
#include "common/Logging.hpp"

// Step 1 skeleton (implementation-plan.md §11): load the config, log it and stop.
// Storage, the HTTP server and the sync are wired in here from Step 4 on (§7.9).
int main() {
    common::initLogging("cist-syncer");
    try {
        const auto config = syncer::Config::fromEnv();
        // databaseUrl is not logged: a libpq connection string may contain a password
        spdlog::info("hello from cist-syncer: port {}, NURE group {}, calendar {}",
                     config.port, config.nureGroup, config.calendarId);
        return 0;
    } catch (const std::exception& e) {
        spdlog::critical("startup failed: {}", e.what());
        return 1;
    }
}
