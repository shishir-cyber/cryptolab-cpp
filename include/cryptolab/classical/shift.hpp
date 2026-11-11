#pragma once
#include <string>
#include <string_view>

namespace cryptolab::classical {

/// Shift cipher: C = (P + k) mod 26. Case is preserved, non-letters pass through.
std::string shift_encrypt(std::string_view plaintext, int key);
std::string shift_decrypt(std::string_view ciphertext, int key);

/// Caesar cipher is the shift cipher with k = 3.
std::string caesar_encrypt(std::string_view plaintext);
std::string caesar_decrypt(std::string_view ciphertext);

}  // namespace cryptolab::classical
