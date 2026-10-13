#include "common/Env.hpp"

#include <cstdlib>
#include <stdexcept>

namespace common {

std::string requireEnv(const char* name) {
    const char* value = std::getenv(name);
    if (value == nullptr || *value == '\0') {
        throw std::runtime_error(std::string{"missing environment variable "} + name);
    }
    return value;
}

std::string envOr(const char* name, std::string fallback) {
    const char* value = std::getenv(name);
    if (value == nullptr || *value == '\0') {
        return fallback;
    }
    return value;
}

}  // namespace common
