#pragma once
#include <string>
#include <string_view>

namespace cryptolab::classical {

/// Affine cipher: C = (a*P + b) mod 26. Requires gcd(a, 26) == 1, otherwise
/// decryption would be impossible (no modular inverse of a). Throws std::invalid_argument.
std::string affine_encrypt(std::string_view plaintext, int a, int b);
std::string affine_decrypt(std::string_view ciphertext, int a, int b);

}  // namespace cryptolab::classical
