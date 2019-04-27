#include "ecore/crypto.h"

#include <sodium.h>

#include <stdexcept>

namespace ecore::crypto {
namespace {

ciphertext new_ciphertext(size_t plaintext_length) {
    return ciphertext(plaintext_length + crypto_box_MACBYTES);
}

plaintext new_plaintext(size_t ciphertext_length) {
    return plaintext(ciphertext_length - crypto_box_MACBYTES, '@');
}

}

void init_crypto() {
    if (sodium_init() < 0) {
        throw std::runtime_error("bad stuff happened");
    }
}

std::pair<public_key, secret_key> new_keypair() {
    public_key pk;
    secret_key sk;
    crypto_box_keypair(pk.data(), sk.data());

    return std::make_pair(pk, sk);
}

nonce new_nonce() {
    nonce n;
    randombytes_buf(n.data(), n.size());
    return n;
}

ciphertext encrypt(
        const secret_key &sender,
        const public_key &receiver,
        const nonce &nonce,
        const plaintext &plain) {
    ciphertext cipher{new_ciphertext(plain.size())};
    if (crypto_box_easy(
            cipher.data(),
            reinterpret_cast<const uint8_t *>(plain.data()),
            plain.size(),
            nonce.data(),
            receiver.data(),
            sender.data()) != 0) {
        throw std::runtime_error("encryption failed");
    }

    return cipher;
}

plaintext decrypt(
        const secret_key &receiver,
        const public_key &sender,
        const nonce &nonce,
        const ciphertext &cipher) {
    plaintext plain = new_plaintext(cipher.size());
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
    return randombytes_random();
}

}
