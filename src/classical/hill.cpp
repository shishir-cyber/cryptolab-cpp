#include "cryptolab/classical/hill.hpp"

#include <stdexcept>

#include "cryptolab/classical/util.hpp"

namespace cryptolab::classical {

Hill2::Hill2(int a, int b, int c, int d)
    : a_(mod(a, 26)), b_(mod(b, 26)), c_(mod(c, 26)), d_(mod(d, 26)) {
  const int det = mod(a_ * d_ - b_ * c_, 26);
  const int det_inv = mod_inverse(det, 26);
  if (det_inv < 0) throw std::invalid_argument("hill: key matrix is not invertible mod 26");
  // inverse = det^-1 * adjugate = det^-1 * [[d, -b], [-c, a]]
  ia_ = mod(det_inv * d_, 26);
  ib_ = mod(-det_inv * b_, 26);
  ic_ = mod(-det_inv * c_, 26);
  id_ = mod(det_inv * a_, 26);
}

std::string Hill2::apply(std::string_view text, int m00, int m01, int m10, int m11) const {
  std::string s = letters_only_upper(text);
  if (s.size() % 2 != 0) s.push_back('X');
  std::string out;
  out.reserve(s.size());
  for (std::size_t i = 0; i < s.size(); i += 2) {
    const int x = s[i] - 'A', y = s[i + 1] - 'A';
    out.push_back(static_cast<char>('A' + mod(m00 * x + m01 * y, 26)));
    out.push_back(static_cast<char>('A' + mod(m10 * x + m11 * y, 26)));
  }
  return out;
}

std::string Hill2::encrypt(std::string_view plaintext) const {
  return apply(plaintext, a_, b_, c_, d_);
}
std::string Hill2::decrypt(std::string_view ciphertext) const {
  return apply(ciphertext, ia_, ib_, ic_, id_);
}

}  // namespace cryptolab::classical
