#include <gtest/gtest.h>

#include "cryptolab/version.hpp"

TEST(Smoke, VersionIsSet) {
  EXPECT_FALSE(cryptolab::version().empty());
  EXPECT_EQ(cryptolab::version(), "0.0.1");
}
