#pragma once
#include <string>
#include <string_view>

namespace cryptolab::classical {

/// Columnar transposition: write the text row by row under the keyword, then read the columns
/// in alphabetical order of the keyword letters (ties: left to right).
/// Short last row is padded with 'X'; decryption returns that padding as-is.
/// Every character (including spaces) is treated as part of the text.
std::string columnar_encrypt(std::string_view plaintext, std::string_view key);
std::string columnar_decrypt(std::string_view ciphertext, std::string_view key);

}  // namespace cryptolab::classical
