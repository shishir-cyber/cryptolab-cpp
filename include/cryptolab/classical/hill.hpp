#pragma once
#include <string>
#include <string_view>

namespace cryptolab::classical {

/// Hill cipher with a 2x2 key matrix [[a, b], [c, d]] mod 26.
/// Needs gcd(det, 26) == 1 so the matrix is invertible (throws std::invalid_argument).
/// Text is reduced to uppercase letters and padded with 'X' to an even length.
class Hill2 {
 public:
  Hill2(int a, int b, int c, int d);

  std::string encrypt(std::string_view plaintext) const;
  std::string decrypt(std::string_view ciphertext) const;

 private:
  std::string apply(std::string_view text, int m00, int m01, int m10, int m11) const;
  int a_, b_, c_, d_;
  int ia_, ib_, ic_, id_;  // inverse matrix
};

}  // namespace cryptolab::classical
