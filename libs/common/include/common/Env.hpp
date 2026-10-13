#pragma once

#include <string>

namespace common {

// Returns the variable's value. Throws std::runtime_error if it is missing or empty,
// so a misconfigured container stops at startup instead of failing at 07:00.
std::string requireEnv(const char* name);

// Returns the variable's value, or `fallback` if it is missing or empty.
std::string envOr(const char* name, std::string fallback);

}  // namespace common
