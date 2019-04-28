#include "ecore/crypto.h"

#include <catch2/catch.hpp>

using namespace ecore::crypto;

namespace {

TEST_CASE("Key generation seems sensible") {
    const auto bob = new_keypair();
    const auto alice = new_keypair();

    REQUIRE(bob.public_key != bob.secret_key);
    REQUIRE(bob.public_key != alice.public_key);
}

TEST_CASE("Encryption works") {
    const auto bob = new_keypair();
    const auto alice = new_keypair();
    const auto nonce = new_nonce();
    const std::string plain{"something about a quick brown fox"};

    const ciphertext cipher = encrypt(
            bob.secret_key,
            alice.public_key,
            nonce,
            plain);

    REQUIRE(std::string(begin(cipher), end(cipher)) != plain);
    REQUIRE(plain == decrypt(alice.secret_key, bob.public_key, nonce, cipher));
}

}
