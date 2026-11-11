#include <gtest/gtest.h>

#include <stdexcept>

#include "cryptolab/classical/transposition.hpp"

using namespace cryptolab::classical;

TEST(Transposition, HandVerifiedVector) {
  // Grid (2 columns): AB / CD / EF. Key "BA": read column 2 (A) first? No: sort B,A -> A first.
  // Column "A" is index 1 -> B D F ; then column "B" is index 0 -> A C E.
  EXPECT_EQ(columnar_encrypt("ABCDEF", "BA"), "BDFACE");
  EXPECT_EQ(columnar_decrypt("BDFACE", "BA"), "ABCDEF");
}

TEST(Transposition, PadsShortLastRow) {
  EXPECT_EQ(columnar_decrypt(columnar_encrypt("ABCDE", "ZEBRAS"), "ZEBRAS"), "ABCDEX");
}

TEST(Transposition, RoundTripWithSpaces) {
  const std::string msg = "WE ARE DISCOVERED FLEE AT ONCE!";
  const std::string back = columnar_decrypt(columnar_encrypt(msg, "ZEBRAS"), "ZEBRAS");
  EXPECT_EQ(back.substr(0, msg.size()), msg);
}

TEST(Transposition, RepeatedKeyLettersGoLeftToRight) {
  EXPECT_EQ(columnar_encrypt("ABCD", "AA"), "ACBD");
}

TEST(Transposition, Errors) {
  EXPECT_THROW(columnar_encrypt("HI", ""), std::invalid_argument);
  EXPECT_THROW(columnar_decrypt("ABCDE", "KEY"), std::invalid_argument);
}
