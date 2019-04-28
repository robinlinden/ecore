#include "ecore/crypto.h"

#include <catch2/catch.hpp>

using namespace ecore::crypto;

namespace {

TEST_CASE("Key generation seems sensible") {
    const auto bob = new_keypair();
    const auto alice = new_keypair();

    REQUIRE(bob.first != bob.second);
    REQUIRE(bob.first != alice.first);
}

TEST_CASE("Encryption works") {
    const auto bob = new_keypair();
    const auto alice = new_keypair();
    const auto nonce = new_nonce();
    const std::string message{"something about a quick brown fox"};

    const ciphertext cipher = encrypt(bob.second, alice.first, nonce, message);

    REQUIRE(std::string(begin(cipher), end(cipher)) != message);
    REQUIRE(message == decrypt(alice.second, bob.first, nonce, cipher));
}

}
