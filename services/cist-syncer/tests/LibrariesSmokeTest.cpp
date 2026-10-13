// Proves that every library syncer_core links is found, compiles and links, without touching the
// network outside this machine. Delete a test once real code and tests cover that library.

#include <string>
#include <thread>

#include <cpr/cpr.h>
#include <gtest/gtest.h>
#include <httplib.h>
#include <jwt-cpp/traits/nlohmann-json/defaults.h>   // vcpkg builds jwt-cpp without picojson
#include <nlohmann/json.hpp>
#include <openssl/evp.h>
#include <pqxx/pqxx>

TEST(SyncerLibrariesTest, NlohmannJsonParses) {
    const auto parsed = nlohmann::json::parse(R"({"status": "ok"})");
    EXPECT_EQ(parsed.at("status").get<std::string>(), "ok");
}

TEST(SyncerLibrariesTest, OpenSslComputesSha1) {
    unsigned char digest[EVP_MAX_MD_SIZE];
    unsigned int length = 0;
    ASSERT_EQ(EVP_Digest("abc", 3, digest, &length, EVP_sha1(), nullptr), 1);
    EXPECT_EQ(length, 20u);
    EXPECT_EQ(digest[0], 0xA9);          // SHA-1("abc") = a9993e36...
}

TEST(SyncerLibrariesTest, JwtCppSignsAndDecodes) {
    const auto token = jwt::create().set_issuer("cist-syncer").sign(jwt::algorithm::hs256{"secret"});
    EXPECT_EQ(jwt::decode(token).get_issuer(), "cist-syncer");
}

TEST(SyncerLibrariesTest, HttplibServerAnswersCprClient) {
    httplib::Server server;
    server.Get("/health", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("up", "text/plain");
    });
    const int port = server.bind_to_any_port("127.0.0.1");
    std::thread listener([&] { server.listen_after_bind(); });
    server.wait_until_ready();

    const cpr::Response response = cpr::Get(cpr::Url{"http://127.0.0.1:" + std::to_string(port) + "/health"});

    server.stop();
    listener.join();                     // join before any EXPECT can end the test
    EXPECT_EQ(response.status_code, 200);
    EXPECT_EQ(response.text, "up");
}

TEST(SyncerLibrariesTest, LibpqxxReportsRefusedConnection) {
    // Nothing listens on port 1, so libpq fails immediately. No PostgreSQL server needed.
    EXPECT_THROW(pqxx::connection{"host=127.0.0.1 port=1 connect_timeout=2"}, pqxx::broken_connection);
}
