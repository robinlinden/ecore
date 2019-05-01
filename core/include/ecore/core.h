#pragma once

#include <array>
#include <cstdint>

namespace ecore::core {

using public_key = std::array<uint8_t, 32>;
using secret_key = std::array<uint8_t, 32>;

struct keypair {
    public_key public_key;
    secret_key secret_key;
};

}
