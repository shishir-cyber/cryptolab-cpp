#include <gtest/gtest.h>

#include <stdexcept>
#include <string>

#include "cryptolab/classical/playfair.hpp"

using namespace cryptolab::classical;

TEST(Playfair, KeySquare) {
  Playfair p("PLAYFAIR EXAMPLE");
  const std::string sq(p.square().begin(), p.square().end());
  EXPECT_EQ(sq, "PLAYFIREXMBCDGHKNOQSTUVWZ");
}

TEST(Playfair, WikipediaVector) {
  Playfair p("PLAYFAIR EXAMPLE");
  EXPECT_EQ(p.encrypt("Hide the gold in the tree stump"), "BMODZBXDNABEKUDMUIXMMOUVIF");
}

TEST(Playfair, DecryptRestoresPaddedPlaintext) {
  Playfair p("PLAYFAIR EXAMPLE");
  // The doubled E in TREE gets an X inserted between them.
  EXPECT_EQ(p.decrypt("BMODZBXDNABEKUDMUIXMMOUVIF"), "HIDETHEGOLDINTHETREXESTUMP");
}

TEST(Playfair, OddLengthIsPadded) {
  Playfair p("MONARCHY");
  EXPECT_EQ(p.decrypt(p.encrypt("ABC")), "ABCX");
}

TEST(Playfair, JIsTreatedAsI) {
  Playfair p("KEY");
  EXPECT_EQ(p.encrypt("JAM"), p.encrypt("IAM"));
}

TEST(Playfair, OddCiphertextThrows) {
  Playfair p("KEY");
  EXPECT_THROW(p.decrypt("ABC"), std::invalid_argument);
}
