#include <gtest/gtest.h>

#include "cryptolab/classical/shift.hpp"

using namespace cryptolab::classical;

TEST(Shift, CaesarKnownVector) {
  EXPECT_EQ(caesar_encrypt("HELLOWORLD"), "KHOORZRUOG");
  EXPECT_EQ(caesar_decrypt("KHOORZRUOG"), "HELLOWORLD");
}

TEST(Shift, PreservesCaseAndPunctuation) {
  EXPECT_EQ(shift_encrypt("Attack at Dawn!", 1), "Buubdl bu Ebxo!");
}

TEST(Shift, WrapsAround) { EXPECT_EQ(shift_encrypt("XYZ", 3), "ABC"); }

TEST(Shift, RoundTripForAllKeys) {
  for (int k = -30; k <= 30; ++k)
    EXPECT_EQ(shift_decrypt(shift_encrypt("The Quick Brown Fox", k), k), "The Quick Brown Fox");
}

TEST(Shift, KeyZeroAnd26AreIdentity) {
  EXPECT_EQ(shift_encrypt("Hello", 0), "Hello");
  EXPECT_EQ(shift_encrypt("Hello", 26), "Hello");
}
