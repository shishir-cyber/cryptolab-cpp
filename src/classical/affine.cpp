#include "cryptolab/classical/affine.hpp"

#include <stdexcept>

#include "cryptolab/classical/util.hpp"

namespace cryptolab::classical {
namespace {

char apply(char c, int mul, int add) {
  if (is_upper(c)) return static_cast<char>('A' + mod(mul * (c - 'A') + add, 26));
  if (is_lower(c)) return static_cast<char>('a' + mod(mul * (c - 'a') + add, 26));
  return c;
}

void check_key(int a) {
  if (gcd(a, 26) != 1) throw std::invalid_argument("affine: 'a' must be coprime with 26");
}

}  // namespace

std::string affine_encrypt(std::string_view plaintext, int a, int b) {
  check_key(a);
  std::string out;
  out.reserve(plaintext.size());
  for (char c : plaintext) out.push_back(apply(c, mod(a, 26), mod(b, 26)));
  return out;
}

std::string affine_decrypt(std::string_view ciphertext, int a, int b) {
  check_key(a);
  // P = a^-1 * (C - b) = a^-1 * C - a^-1 * b
  const int inv = mod_inverse(a, 26);
  std::string out;
  out.reserve(ciphertext.size());
  for (char c : ciphertext) out.push_back(apply(c, inv, -inv * b));
  return out;
}

}  // namespace cryptolab::classical
