// Proves that every library bot_core links is found, compiles and links, without touching the
// network outside this machine. Delete a test once real code and tests cover that library.

#include <chrono>

#include <cpr/cpr.h>
#include <gtest/gtest.h>
#include <tgbot/tgbot.h>

TEST(BotLibrariesTest, TgBotConstructsWithoutNetwork) {
    const TgBot::Bot bot{"123456:TEST-TOKEN"};      // the constructor makes no request
    EXPECT_EQ(bot.getToken(), "123456:TEST-TOKEN");
}

TEST(BotLibrariesTest, CprReportsNoResponseInsteadOfThrowing) {
    // This is what "cist-syncer unreachable" (case 32) looks like: status 0 and an error, no exception.
    const cpr::Response response = cpr::Get(cpr::Url{"http://127.0.0.1:1/"}, cpr::Timeout{std::chrono::seconds{2}});
    EXPECT_TRUE(static_cast<bool>(response.error));
    EXPECT_EQ(response.status_code, 0);
}
