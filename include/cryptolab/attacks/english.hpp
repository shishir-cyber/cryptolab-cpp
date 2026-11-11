#pragma once
#include <array>
#include <string_view>

namespace cryptolab::attacks {

/// Relative frequency of each letter A..Z in typical English text (sums to ~1).
const std::array<double, 26>& english_frequencies();

/// Chi-squared distance between the letter counts of `text` and English.
/// LOWER = looks more like English. Only letters are counted. Returns a huge value if no letters.
double chi_squared(std::string_view text);

/// Index of Coincidence: probability that two random letters of `text` are equal.
/// English ~ 0.067, uniformly random letters ~ 0.038. Returns 0 for fewer than 2 letters.
double index_of_coincidence(std::string_view text);

}  // namespace cryptolab::attacks
