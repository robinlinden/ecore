#ifndef ECORE_CORE_H
#define ECORE_CORE_H

#include <array>
#include <cstdint>

namespace ecore::core {

using PublicKey = std::array<uint8_t, 32>;
using SecretKey = std::array<uint8_t, 32>;

struct KeyPair {
    PublicKey public_key;
    SecretKey secret_key;
};

}

#endif
