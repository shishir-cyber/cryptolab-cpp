#pragma once
#include <string>
#include <string_view>

namespace cryptolab::classical {

/// Mathematical modulo: result is always in [0, m), even for negative x.
/// (In C++, -3 % 26 is -3, which is not what cipher math wants.)
constexpr int mod(int x, int m) {
  const int r = x % m;
  return r < 0 ? r + m : r;
}

constexpr bool is_upper(char c) { return c >= 'A' && c <= 'Z'; }
constexpr bool is_lower(char c) { return c >= 'a' && c <= 'z'; }
constexpr bool is_letter(char c) { return is_upper(c) || is_lower(c); }

/// Shift one letter by k positions (wraps around the alphabet). Non-letters are untouched.
constexpr char rotate_letter(char c, int k) {
  if (is_upper(c)) return static_cast<char>('A' + mod(c - 'A' + k, 26));
  if (is_lower(c)) return static_cast<char>('a' + mod(c - 'a' + k, 26));
  return c;
}

/// Keep only the letters of `s`, converted to UPPERCASE.
inline std::string letters_only_upper(std::string_view s) {
  std::string out;
  out.reserve(s.size());
  for (char c : s) {
    if (is_upper(c))
      out.push_back(c);
    else if (is_lower(c))
      out.push_back(static_cast<char>(c - 'a' + 'A'));
  }
  return out;
}

/// Greatest common divisor (Euclid's algorithm).
int gcd(int a, int b);

/// Modular inverse of a modulo m using the Extended Euclidean Algorithm.
/// Returns -1 if no inverse exists (i.e. gcd(a, m) != 1).
int mod_inverse(int a, int m);

}  // namespace cryptolab::classical
