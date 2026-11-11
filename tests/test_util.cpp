#include <gtest/gtest.h>

#include "cryptolab/classical/util.hpp"

using namespace cryptolab::classical;

TEST(Util, ModHandlesNegatives) {
  EXPECT_EQ(mod(-3, 26), 23);
  EXPECT_EQ(mod(29, 26), 3);
  EXPECT_EQ(mod(0, 26), 0);
}

TEST(Util, Gcd) {
  EXPECT_EQ(gcd(12, 18), 6);
  EXPECT_EQ(gcd(7, 26), 1);
  EXPECT_EQ(gcd(0, 5), 5);
}

TEST(Util, ModInverse) {
  EXPECT_EQ(mod_inverse(5, 26), 21);  // 5 * 21 = 105 = 4*26 + 1
  EXPECT_EQ(mod_inverse(3, 7), 5);
  EXPECT_EQ(mod_inverse(2, 26), -1);  // not coprime -> no inverse
}

TEST(Util, ModInverseIsCorrectForAllCoprimes) {
  for (int a = 1; a < 26; ++a) {
    if (gcd(a, 26) != 1) continue;
    EXPECT_EQ(mod(a * mod_inverse(a, 26), 26), 1) << "a=" << a;
  }
}

TEST(Util, LettersOnlyUpper) { EXPECT_EQ(letters_only_upper("Hi, there! 42"), "HITHERE"); }
