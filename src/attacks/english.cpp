#include "cryptolab/attacks/english.hpp"

#include <cstddef>

#include "cryptolab/classical/util.hpp"

namespace cryptolab::attacks {

const std::array<double, 26>& english_frequencies() {
  static const std::array<double, 26> f = {
      0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966,
      0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987,
      0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};
  return f;
}

namespace {
std::array<std::size_t, 26> count_letters(std::string_view text, std::size_t& total) {
  std::array<std::size_t, 26> counts{};
  total = 0;
  for (char c : classical::letters_only_upper(text)) {
    ++counts[static_cast<std::size_t>(c - 'A')];
    ++total;
  }
  return counts;
}
}  // namespace

double chi_squared(std::string_view text) {
  std::size_t total = 0;
  const auto counts = count_letters(text, total);
  if (total == 0) return 1e300;
  const auto& freq = english_frequencies();
  double chi = 0.0;
  for (std::size_t i = 0; i < 26; ++i) {
    const double expected = freq[i] * static_cast<double>(total);
    const double diff = static_cast<double>(counts[i]) - expected;
    chi += diff * diff / expected;
  }
  return chi;
}

double index_of_coincidence(std::string_view text) {
  std::size_t total = 0;
  const auto counts = count_letters(text, total);
  if (total < 2) return 0.0;
  double sum = 0.0;
  for (std::size_t n : counts) sum += static_cast<double>(n) * static_cast<double>(n - (n ? 1 : 0));
  return sum / (static_cast<double>(total) * static_cast<double>(total - 1));
}

}  // namespace cryptolab::attacks
