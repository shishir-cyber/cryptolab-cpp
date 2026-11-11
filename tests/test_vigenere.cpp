#include <gtest/gtest.h>

#include <stdexcept>

#include "cryptolab/classical/vigenere.hpp"

using namespace cryptolab::classical;

TEST(Vigenere, KnownVector) {
  EXPECT_EQ(vigenere_encrypt("ATTACKATDAWN", "LEMON"), "LXFOPVEFRNHR");
  EXPECT_EQ(vigenere_decrypt("LXFOPVEFRNHR", "LEMON"), "ATTACKATDAWN");
}

TEST(Vigenere, NonLettersDoNotConsumeKey) {
  EXPECT_EQ(vigenere_encrypt("AT TACK", "LEMON"), "LX FOPV");
}

TEST(Vigenere, KeyCaseDoesNotMatter) {
  EXPECT_EQ(vigenere_encrypt("ATTACKATDAWN", "lemon"), "LXFOPVEFRNHR");
}

TEST(Vigenere, SingleLetterKeyIsAShift) { EXPECT_EQ(vigenere_encrypt("ABC", "D"), "DEF"); }

TEST(Vigenere, RejectsBadKeys) {
  EXPECT_THROW(vigenere_encrypt("HI", ""), std::invalid_argument);
  EXPECT_THROW(vigenere_encrypt("HI", "KEY1"), std::invalid_argument);
}

TEST(Vigenere, RoundTripMixedCase) {
  const std::string msg = "Hello, World! Cryptography is fun.";
  EXPECT_EQ(vigenere_decrypt(vigenere_encrypt(msg, "Secret"), "Secret"), msg);
}
