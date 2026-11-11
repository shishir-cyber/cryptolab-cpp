#include "cryptolab/attacks/break_classical.hpp"

#include <limits>
#include <vector>

#include "cryptolab/attacks/english.hpp"
#include "cryptolab/classical/affine.hpp"
#include "cryptolab/classical/shift.hpp"
#include "cryptolab/classical/util.hpp"
#include "cryptolab/classical/vigenere.hpp"

namespace cryptolab::attacks {

ShiftResult break_shift(std::string_view ciphertext) {
  ShiftResult best{0, std::string(ciphertext), std::numeric_limits<double>::max()};
  for (int k = 0; k < 26; ++k) {
    std::string candidate = classical::shift_decrypt(ciphertext, k);
    const double score = chi_squared(candidate);
    if (score < best.score) best = {k, std::move(candidate), score};
  }
  return best;
}

AffineResult break_affine(std::string_view ciphertext) {
  AffineResult best{1, 0, std::string(ciphertext), std::numeric_limits<double>::max()};
  for (int a = 1; a < 26; ++a) {
    if (classical::gcd(a, 26) != 1) continue;
    for (int b = 0; b < 26; ++b) {
      std::string candidate = classical::affine_decrypt(ciphertext, a, b);
      const double score = chi_squared(candidate);
      if (score < best.score) best = {a, b, std::move(candidate), score};
    }
  }
  return best;
}

namespace {

// Average Index of Coincidence over the `len` columns obtained by taking every len-th letter.
double average_column_ic(const std::string& letters, std::size_t len) {
  double total = 0.0;
  for (std::size_t start = 0; start < len; ++start) {
    std::string column;
    for (std::size_t i = start; i < letters.size(); i += len) column.push_back(letters[i]);
    total += index_of_coincidence(column);
  }
  return total / static_cast<double>(len);
}

}  // namespace

std::size_t estimate_vigenere_key_length(std::string_view ciphertext, std::size_t max_len) {
  const std::string letters = classical::letters_only_upper(ciphertext);
  constexpr double kEnglishLike = 0.060;  // English ~0.067, random ~0.038
  std::size_t best_len = 1;
  double best_ic = -1.0;
  for (std::size_t len = 1; len <= max_len && len < letters.size(); ++len) {
    const double ic = average_column_ic(letters, len);
    if (ic >= kEnglishLike) return len;  // smallest length that looks like English columns
    if (ic > best_ic) {
      best_ic = ic;
      best_len = len;
    }
  }
  return best_len;  // fallback: the best-scoring length
}

VigenereResult break_vigenere(std::string_view ciphertext, std::size_t max_len) {
  const std::string letters = classical::letters_only_upper(ciphertext);
  const std::size_t len = estimate_vigenere_key_length(ciphertext, max_len);

  std::string key;
  for (std::size_t start = 0; start < len; ++start) {
    std::string column;
    for (std::size_t i = start; i < letters.size(); i += len) column.push_back(letters[i]);
    key.push_back(static_cast<char>('A' + break_shift(column).key));
  }
  return {key, classical::vigenere_decrypt(ciphertext, key), len};
}

}  // namespace cryptolab::attacks
