#include "cryptolab/classical/vigenere.hpp"

#include <stdexcept>
#include <vector>

#include "cryptolab/classical/util.hpp"

namespace cryptolab::classical {
namespace {

std::vector<int> key_shifts(std::string_view key) {
  std::vector<int> shifts;
  for (char c : key) {
    if (!is_letter(c)) throw std::invalid_argument("vigenere: key must contain only letters");
    shifts.push_back(is_upper(c) ? c - 'A' : c - 'a');
  }
  if (shifts.empty()) throw std::invalid_argument("vigenere: key must not be empty");
  return shifts;
}

std::string run(std::string_view text, std::string_view key, int sign) {
  const std::vector<int> shifts = key_shifts(key);
  std::string out;
  out.reserve(text.size());
  std::size_t i = 0;
  for (char c : text) {
    if (is_letter(c)) {
      out.push_back(rotate_letter(c, sign * shifts[i % shifts.size()]));
      ++i;
    } else {
      out.push_back(c);
    }
  }
  return out;
}

}  // namespace

std::string vigenere_encrypt(std::string_view plaintext, std::string_view key) {
  return run(plaintext, key, +1);
}
std::string vigenere_decrypt(std::string_view ciphertext, std::string_view key) {
  return run(ciphertext, key, -1);
}

}  // namespace cryptolab::classical
