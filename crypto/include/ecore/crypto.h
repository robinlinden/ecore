#pragma once

#include "ecore/core.h"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace ecore::crypto {

using Ciphertext = std::vector<uint8_t>;
using Plaintext = std::string;

using Nonce = std::array<uint8_t, 24>;

struct EncryptionResult {
    Nonce nonce;
    Ciphertext ciphertext;
};

core::KeyPair new_keypair();

Nonce new_nonce();

EncryptionResult encrypt(
        const core::SecretKey &sender,
        const core::PublicKey &receiver,
        const Plaintext &plain);
Plaintext decrypt(
        const core::SecretKey &receiver,
        const core::PublicKey &sender,
        const Nonce &nonce,
        const Ciphertext &cipher);

uint32_t random_bytes();

}
