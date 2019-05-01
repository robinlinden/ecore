#pragma once

#include "ecore/core.h"

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace ecore::crypto {

using ciphertext = std::vector<uint8_t>;
using plaintext = std::string;

using nonce = std::array<uint8_t, 24>;

core::keypair new_keypair();

nonce new_nonce();

ciphertext encrypt(
        const core::secret_key &sender,
        const core::public_key &receiver,
        const nonce &nonce,
        const plaintext &plain);
plaintext decrypt(
        const core::secret_key &receiver,
        const core::public_key &sender,
        const nonce &nonce,
        const ciphertext &cipher);

uint32_t random_bytes();

}
