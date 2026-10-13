#pragma once

#include <string>

namespace syncer {

// Everything cist-syncer reads from the environment, loaded once at startup (implementation-plan.md §7.9).
// semesterOverride and syncSettings() join this struct once Semester and SyncSettings exist (§7.3, §7.7).
struct Config {
    int port = 8080;
    std::string databaseUrl;
    std::string nureGroup;
    std::string cistHost = "https://cist.nure.ua";
    std::string cistMirrorHost = "https://cist2.nure.ua";
    std::string calendarId;
    std::string googleKeyFile;
    double guardMinRatio = 0.7;

    // Throws std::runtime_error naming the first missing or invalid variable.
    static Config fromEnv();
};

}  // namespace syncer
