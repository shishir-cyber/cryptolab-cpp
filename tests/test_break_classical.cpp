#include <gtest/gtest.h>

#include "cryptolab/attacks/break_classical.hpp"
#include "cryptolab/attacks/english.hpp"
#include "cryptolab/classical/affine.hpp"
#include "cryptolab/classical/shift.hpp"
#include "cryptolab/classical/util.hpp"
#include "cryptolab/classical/vigenere.hpp"
#include "sample_text.hpp"

using namespace cryptolab;

TEST(English, FrequenciesSumToAboutOne) {
  double sum = 0;
  for (double f : attacks::english_frequencies()) sum += f;
  EXPECT_NEAR(sum, 1.0, 0.01);
}

TEST(English, EnglishScoresBetterThanGibberish) {
  EXPECT_LT(attacks::chi_squared(kSampleEnglish),
            attacks::chi_squared(classical::shift_encrypt(kSampleEnglish, 7)));
}

TEST(English, IndexOfCoincidence) {
  EXPECT_NEAR(attacks::index_of_coincidence(kSampleEnglish), 0.067, 0.012);
  EXPECT_EQ(attacks::index_of_coincidence("A"), 0.0);
}

TEST(BreakShift, RecoversEveryKey) {
  for (int k = 0; k < 26; ++k) {
    const auto ct = classical::shift_encrypt(kSampleEnglish, k);
    const auto r = attacks::break_shift(ct);
    EXPECT_EQ(r.key, k);
    EXPECT_EQ(r.plaintext, kSampleEnglish);
  }
}

TEST(BreakAffine, RecoversKey) {
  const auto ct = classical::affine_encrypt(kSampleEnglish, 7, 11);
  const auto r = attacks::break_affine(ct);
  EXPECT_EQ(r.a, 7);
  EXPECT_EQ(r.b, 11);
  EXPECT_EQ(r.plaintext, kSampleEnglish);
}

TEST(BreakVigenere, EstimatesKeyLength) {
  const auto ct = classical::vigenere_encrypt(kSampleEnglish, "LEMON");
  EXPECT_EQ(attacks::estimate_vigenere_key_length(ct), 5u);
}

TEST(BreakVigenere, RecoversKeyAndPlaintext) {
  for (const char* key : {"LEMON", "CRYPTO", "KEY", "SECURITY"}) {
    const auto ct = classical::vigenere_encrypt(kSampleEnglish, key);
    const auto r = attacks::break_vigenere(ct);
    EXPECT_EQ(r.key, key);
    EXPECT_EQ(r.plaintext, kSampleEnglish);
  }
}
