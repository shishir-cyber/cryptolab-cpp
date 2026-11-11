#include <gtest/gtest.h>

#include <stdexcept>

#include "cryptolab/classical/affine.hpp"
#include "cryptolab/classical/util.hpp"

using namespace cryptolab::classical;

TEST(Affine, KnownVector) {
  // Classic textbook example: a=5, b=8.
  EXPECT_EQ(affine_encrypt("AFFINECIPHER", 5, 8), "IHHWVCSWFRCP");
  EXPECT_EQ(affine_decrypt("IHHWVCSWFRCP", 5, 8), "AFFINECIPHER");
}

TEST(Affine, RejectsNonCoprimeA) {
  EXPECT_THROW(affine_encrypt("HELLO", 2, 3), std::invalid_argument);
  EXPECT_THROW(affine_decrypt("HELLO", 13, 3), std::invalid_argument);
}

TEST(Affine, RoundTripAllValidKeys) {
  const std::string msg = "Meet Me At Noon, Quietly.";
  for (int a = 1; a < 26; ++a) {
    if (gcd(a, 26) != 1) continue;
    for (int b = 0; b < 26; ++b)
      EXPECT_EQ(affine_decrypt(affine_encrypt(msg, a, b), a, b), msg) << a << "," << b;
  }
}

TEST(Affine, A1IsAShiftCipher) { EXPECT_EQ(affine_encrypt("ABC", 1, 3), "DEF"); }
