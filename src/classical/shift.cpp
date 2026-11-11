#include "cryptolab/classical/shift.hpp"

#include "cryptolab/classical/util.hpp"

namespace cryptolab::classical {

std::string shift_encrypt(std::string_view plaintext, int key) {
  std::string out;
  out.reserve(plaintext.size());
  for (char c : plaintext) out.push_back(rotate_letter(c, key));
  return out;
}

std::string shift_decrypt(std::string_view ciphertext, int key) {
  return shift_encrypt(ciphertext, -key);
}

std::string caesar_encrypt(std::string_view plaintext) { return shift_encrypt(plaintext, 3); }
std::string caesar_decrypt(std::string_view ciphertext) { return shift_decrypt(ciphertext, 3); }

}  // namespace cryptolab::classical
