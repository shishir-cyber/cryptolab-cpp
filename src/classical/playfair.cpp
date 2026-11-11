#include "cryptolab/classical/playfair.hpp"

#include <stdexcept>

#include "cryptolab/classical/util.hpp"

namespace cryptolab::classical {
namespace {

std::string clean(std::string_view s) {
  std::string t = letters_only_upper(s);
  for (char& c : t)
    if (c == 'J') c = 'I';
  return t;
}

}  // namespace

Playfair::Playfair(std::string_view key) {
  position_.fill(-1);
  std::array<bool, 26> used{};
  std::size_t n = 0;
  auto add = [&](char c) {
    const int idx = c - 'A';
    if (used[static_cast<std::size_t>(idx)]) return;
    used[static_cast<std::size_t>(idx)] = true;
    square_[n] = c;
    position_[static_cast<std::size_t>(idx)] = static_cast<int>(n);
    ++n;
  };
  for (char c : clean(key)) add(c);
  for (char c = 'A'; c <= 'Z'; ++c)
    if (c != 'J') add(c);
}

std::string Playfair::transform(std::string_view pairs, int step) const {
  std::string out;
  out.reserve(pairs.size());
  for (std::size_t i = 0; i + 1 < pairs.size(); i += 2) {
    const int pa = position_[static_cast<std::size_t>(pairs[i] - 'A')];
    const int pb = position_[static_cast<std::size_t>(pairs[i + 1] - 'A')];
    const int ra = pa / 5, ca = pa % 5, rb = pb / 5, cb = pb % 5;
    int na, nb;
    if (ra == rb) {  // same row: move horizontally
      na = ra * 5 + mod(ca + step, 5);
      nb = rb * 5 + mod(cb + step, 5);
    } else if (ca == cb) {  // same column: move vertically
      na = mod(ra + step, 5) * 5 + ca;
      nb = mod(rb + step, 5) * 5 + cb;
    } else {  // rectangle: swap columns
      na = ra * 5 + cb;
      nb = rb * 5 + ca;
    }
    out.push_back(square_[static_cast<std::size_t>(na)]);
    out.push_back(square_[static_cast<std::size_t>(nb)]);
  }
  return out;
}

std::string Playfair::encrypt(std::string_view plaintext) const {
  const std::string s = clean(plaintext);
  std::string pairs;
  std::size_t i = 0;
  while (i < s.size()) {
    const char a = s[i];
    char b;
    if (i + 1 < s.size() && s[i + 1] != a) {
      b = s[i + 1];
      i += 2;
    } else {
      b = (a == 'X') ? 'Q' : 'X';  // filler for double letters / odd length
      i += 1;
    }
    pairs.push_back(a);
    pairs.push_back(b);
  }
  return transform(pairs, +1);
}

std::string Playfair::decrypt(std::string_view ciphertext) const {
  const std::string s = clean(ciphertext);
  if (s.size() % 2 != 0) throw std::invalid_argument("playfair: ciphertext length must be even");
  return transform(s, -1);
}

}  // namespace cryptolab::classical
