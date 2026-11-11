#pragma once
#include <cstddef>
#include <string>
#include <string_view>

namespace cryptolab::attacks {

struct ShiftResult {
  int key;                // encryption shift that was most likely used
  std::string plaintext;  // ciphertext decrypted with that key
  double score;           // chi-squared (lower is better)
};

struct AffineResult {
  int a, b;
  std::string plaintext;
  double score;
};

struct VigenereResult {
  std::string key;  // uppercase
  std::string plaintext;
  std::size_t key_length;
};

/// Brute force all 26 shifts and keep the one that looks most like English.
ShiftResult break_shift(std::string_view ciphertext);

/// Brute force all 12*26 = 312 affine keys and keep the most English-looking result.
AffineResult break_affine(std::string_view ciphertext);

/// Estimate the Vigenere key length with the Index of Coincidence.
/// Tries lengths 1..max_len and returns the smallest one that looks "English-like per column".
std::size_t estimate_vigenere_key_length(std::string_view ciphertext, std::size_t max_len = 20);

/// Full Vigenere break: estimate the key length, then solve every column as a shift cipher.
/// Needs a reasonably long ciphertext (a few hundred letters) to be reliable.
VigenereResult break_vigenere(std::string_view ciphertext, std::size_t max_len = 20);

}  // namespace cryptolab::attacks
