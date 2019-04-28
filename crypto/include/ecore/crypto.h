#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace ecore::crypto {

using public_key = std::array<uint8_t, 32>;
using secret_key = std::array<uint8_t, 32>;

using ciphertext = std::vector<uint8_t>;
using plaintext = std::string;

using nonce = std::array<uint8_t, 24>;

std::pair<public_key, secret_key> new_keypair();

nonce new_nonce();

ciphertext encrypt(
        const secret_key &sender,
        const public_key &receiver,
        const nonce &nonce,
        const plaintext &plain);
plaintext decrypt(
        const secret_key &receiver,
        const public_key &sender,
        const nonce &nonce,
        const ciphertext &cipher);

uint32_t random_bytes();

}
