#include "ecore/crypto.h"

#include <sodium.h>

#include <atomic>
#include <stdexcept>

using namespace ecore::core;

namespace ecore::crypto {
namespace {

Ciphertext new_ciphertext(size_t plaintext_length) {
    return Ciphertext(plaintext_length + crypto_box_MACBYTES);
}

Plaintext new_plaintext(size_t ciphertext_length) {
    return Plaintext(ciphertext_length - crypto_box_MACBYTES, '@');
}

void init_crypto_if_needed() {
    static std::atomic<bool> initialized = false;
    if (initialized) {
        return;
    }

    if (sodium_init() < 0) {
        throw std::runtime_error("bad stuff happened");
    }

    initialized = true;
}

}

KeyPair new_keypair() {
    init_crypto_if_needed();

    KeyPair keypair;
    crypto_box_keypair(keypair.public_key.data(), keypair.secret_key.data());

    return keypair;
}

Nonce new_nonce() {
    init_crypto_if_needed();

    Nonce n;
    randombytes_buf(n.data(), n.size());
    return n;
}

EncryptionResult encrypt(
        const SecretKey &sender,
        const PublicKey &receiver,
        const Plaintext &plain) {
    init_crypto_if_needed();

    EncryptionResult result{new_nonce(), new_ciphertext(plain.size())};
    if (crypto_box_easy(
            result.ciphertext.data(),
            reinterpret_cast<const uint8_t *>(plain.data()),
            plain.size(),
            result.nonce.data(),
            receiver.data(),
            sender.data()) != 0) {
        throw std::runtime_error("encryption failed");
    }

    return result;
}

Plaintext decrypt(
        const SecretKey &receiver,
        const PublicKey &sender,
        const Nonce &nonce,
        const Ciphertext &cipher) {
    init_crypto_if_needed();

    Plaintext plain = new_plaintext(cipher.size());
    if (crypto_box_open_easy(
            reinterpret_cast<uint8_t *>(plain.data()),
            cipher.data(),
            cipher.size(),
            nonce.data(),
            sender.data(),
            receiver.data()) != 0) {
        throw std::runtime_error("decryption failed");
    }

    return plain;
}

uint32_t random_bytes() {
    init_crypto_if_needed();

    return randombytes_random();
}

}
