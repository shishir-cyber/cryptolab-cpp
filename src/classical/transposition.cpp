#include "cryptolab/classical/transposition.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace cryptolab::classical {
namespace {

// Column read order: indices of the key sorted by letter (stable, so ties go left to right).
std::vector<std::size_t> column_order(std::string_view key) {
  if (key.empty()) throw std::invalid_argument("transposition: key must not be empty");
  std::vector<std::size_t> order(key.size());
  std::iota(order.begin(), order.end(), std::size_t{0});
  std::stable_sort(order.begin(), order.end(),
                   [&](std::size_t x, std::size_t y) { return key[x] < key[y]; });
  return order;
}

}  // namespace

std::string columnar_encrypt(std::string_view plaintext, std::string_view key) {
  const auto order = column_order(key);
  const std::size_t cols = key.size();
  std::string padded(plaintext);
  while (padded.size() % cols != 0) padded.push_back('X');
  const std::size_t rows = padded.size() / cols;

  std::string out;
  out.reserve(padded.size());
  for (std::size_t col : order)
    for (std::size_t r = 0; r < rows; ++r) out.push_back(padded[r * cols + col]);
  return out;
}

std::string columnar_decrypt(std::string_view ciphertext, std::string_view key) {
  const auto order = column_order(key);
  const std::size_t cols = key.size();
  if (ciphertext.size() % cols != 0)
    throw std::invalid_argument(
        "transposition: ciphertext length must be a multiple of key length");
  const std::size_t rows = ciphertext.size() / cols;

  std::string out(ciphertext.size(), ' ');
  std::size_t k = 0;
  for (std::size_t col : order)
    for (std::size_t r = 0; r < rows; ++r) out[r * cols + col] = ciphertext[k++];
  return out;
}

}  // namespace cryptolab::classical
