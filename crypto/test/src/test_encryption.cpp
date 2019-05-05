#include "ecore/crypto.h"

#include <catch2/catch.hpp>

using namespace ecore::crypto;

namespace {

TEST_CASE("crypto: key generation") {
    const auto bob = new_keypair();
    const auto alice = new_keypair();

    REQUIRE(bob.public_key != bob.secret_key);
    REQUIRE(bob.public_key != alice.public_key);
}

TEST_CASE("crypto: encryption/decryption") {
    const auto bob = new_keypair();
    const auto alice = new_keypair();
    const std::string plain{"something about a quick brown fox"};

    const auto res = encrypt(
            bob.secret_key,
            alice.public_key,
            plain);

    REQUIRE(std::string(begin(res.ciphertext), end(res.ciphertext)) != plain);
    REQUIRE(plain == decrypt(
            alice.secret_key,
            bob.public_key,
            res.nonce,
            res.ciphertext));
}

}
