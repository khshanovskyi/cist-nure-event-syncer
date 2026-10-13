#include <cstdlib>
#include <stdexcept>

#include <gtest/gtest.h>

#include "common/Env.hpp"

namespace {

constexpr const char* kVariable = "CISTSYNC_ENV_TEST";

// Sets an environment variable for the lifetime of this object and removes it in the destructor,
// even when an assertion fails half-way through the test (RAII, like try-with-resources).
class ScopedEnv {
public:
    ScopedEnv(const char* name, const char* value) : name_(name) { setenv(name, value, /*overwrite=*/1); }
    ~ScopedEnv() { unsetenv(name_); }
    ScopedEnv(const ScopedEnv&) = delete;
    ScopedEnv& operator=(const ScopedEnv&) = delete;

private:
    const char* name_;
};

}  // namespace

TEST(EnvTest, RequireEnvReturnsTheValue) {
    const ScopedEnv env{kVariable, "42"};
    EXPECT_EQ(common::requireEnv(kVariable), "42");
}

TEST(EnvTest, RequireEnvThrowsWhenMissing) {
    unsetenv(kVariable);
    EXPECT_THROW(common::requireEnv(kVariable), std::runtime_error);
}

TEST(EnvTest, RequireEnvThrowsWhenEmpty) {
    const ScopedEnv env{kVariable, ""};
    EXPECT_THROW(common::requireEnv(kVariable), std::runtime_error);
}

TEST(EnvTest, EnvOrFallsBackWhenMissingOrEmpty) {
    unsetenv(kVariable);
    EXPECT_EQ(common::envOr(kVariable, "fallback"), "fallback");

    const ScopedEnv env{kVariable, ""};
    EXPECT_EQ(common::envOr(kVariable, "fallback"), "fallback");
}

TEST(EnvTest, EnvOrPrefersTheValue) {
    const ScopedEnv env{kVariable, "value"};
    EXPECT_EQ(common::envOr(kVariable, "fallback"), "value");
}
