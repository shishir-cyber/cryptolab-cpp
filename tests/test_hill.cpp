#include <gtest/gtest.h>

#include <stdexcept>

#include "cryptolab/classical/hill.hpp"

using namespace cryptolab::classical;

TEST(Hill, KnownVector) {
  Hill2 h(3, 3, 2, 5);
  EXPECT_EQ(h.encrypt("HELP"), "HIAT");
  EXPECT_EQ(h.decrypt("HIAT"), "HELP");
}

TEST(Hill, OddLengthIsPadded) {
  Hill2 h(3, 3, 2, 5);
  EXPECT_EQ(h.decrypt(h.encrypt("ABC")), "ABCX");
}

TEST(Hill, RejectsNonInvertibleKey) {
  EXPECT_THROW(Hill2(2, 4, 1, 2), std::invalid_argument);  // det = 0
  EXPECT_THROW(Hill2(2, 0, 0, 2), std::invalid_argument);  // det = 4, gcd(4,26)=2
}

TEST(Hill, RoundTripLongerText) {
  Hill2 h(5, 17, 4, 15);
  EXPECT_EQ(h.decrypt(h.encrypt("CRYPTOGRAPHYISFUN")), "CRYPTOGRAPHYISFUNX");
}
