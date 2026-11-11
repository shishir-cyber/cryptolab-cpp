#pragma once
#include <array>
#include <string>
#include <string_view>

namespace cryptolab::classical {

/// Playfair cipher on a 5x5 key square (I and J share a cell).
/// Encryption: text is reduced to letters, J->I, split into pairs, an 'X' is inserted between
/// equal letters and appended if the length is odd.
/// Decryption returns the padded text as-is (the inserted X's are NOT removed automatically).
class Playfair {
 public:
  explicit Playfair(std::string_view key);

  std::string encrypt(std::string_view plaintext) const;
  std::string decrypt(std::string_view ciphertext) const;

  /// The 5x5 key square in row-major order.
  const std::array<char, 25>& square() const { return square_; }

 private:
  std::string transform(std::string_view pairs, int step) const;

  std::array<char, 25> square_{};
  std::array<int, 26> position_{};  // letter -> index in square_, -1 for 'J'
};

}  // namespace cryptolab::classical
