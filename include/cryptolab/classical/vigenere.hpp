#pragma once
#include <string>
#include <string_view>

namespace cryptolab::classical {

/// Vigenere cipher: each letter is shifted by the matching letter of a repeating key.
/// The key may only contain letters (throws std::invalid_argument otherwise / if empty).
/// Non-letters pass through and do NOT consume a key letter.
std::string vigenere_encrypt(std::string_view plaintext, std::string_view key);
std::string vigenere_decrypt(std::string_view ciphertext, std::string_view key);

}  // namespace cryptolab::classical
