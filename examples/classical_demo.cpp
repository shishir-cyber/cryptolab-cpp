// A small program that uses the library. Edit the messages and keys, rebuild, and run it.
#include <iostream>
#include <string>

#include "cryptolab/attacks/break_classical.hpp"
#include "cryptolab/classical/affine.hpp"
#include "cryptolab/classical/hill.hpp"
#include "cryptolab/classical/playfair.hpp"
#include "cryptolab/classical/shift.hpp"
#include "cryptolab/classical/transposition.hpp"
#include "cryptolab/classical/vigenere.hpp"

using namespace cryptolab;

int main() {
  // ---------- Shift / Caesar ----------
  std::string msg = "Meet me at the library at noon";
  std::string c1 = classical::shift_encrypt(msg, 3);
  std::cout << "[Shift k=3]      " << c1 << "\n";
  std::cout << "  decrypted:     " << classical::shift_decrypt(c1, 3) << "\n\n";

  // ---------- Affine ----------
  std::string c2 = classical::affine_encrypt(msg, 5, 8);
  std::cout << "[Affine a=5,b=8] " << c2 << "\n";
  std::cout << "  decrypted:     " << classical::affine_decrypt(c2, 5, 8) << "\n\n";

  // ---------- Vigenere ----------
  std::string c3 = classical::vigenere_encrypt(msg, "LEMON");
  std::cout << "[Vigenere LEMON] " << c3 << "\n";
  std::cout << "  decrypted:     " << classical::vigenere_decrypt(c3, "LEMON") << "\n\n";

  // ---------- Playfair ----------
  classical::Playfair pf("PLAYFAIR EXAMPLE");
  std::string c4 = pf.encrypt("Hide the gold in the tree stump");
  std::cout << "[Playfair]       " << c4 << "\n";
  std::cout << "  decrypted:     " << pf.decrypt(c4) << "\n\n";

  // ---------- Hill ----------
  classical::Hill2 hill(3, 3, 2, 5);
  std::string c5 = hill.encrypt("HELP");
  std::cout << "[Hill 2x2]       " << c5 << "\n";
  std::cout << "  decrypted:     " << hill.decrypt(c5) << "\n\n";

  // ---------- Columnar transposition ----------
  std::string c6 = classical::columnar_encrypt("WEAREDISCOVERED", "ZEBRAS");
  std::cout << "[Transposition]  " << c6 << "\n";
  std::cout << "  decrypted:     " << classical::columnar_decrypt(c6, "ZEBRAS") << "\n\n";

  // ---------- Attacks: break ciphers WITHOUT knowing the key ----------
  std::cout << "=== ATTACKS ===\n";
  auto s = attacks::break_shift("Phhw ph dw wkh oleudub dw qrrq");
  std::cout << "break_shift found key " << s.key << ": " << s.plaintext << "\n";

  std::string secret =
      "Cryptography is the practice of securing communication in the presence of adversaries. "
      "For many centuries people protected their messages with simple substitutions, shifting "
      "every letter of the alphabet by a fixed amount or replacing each letter with another one "
      "according to a secret rule. These ciphers look very strong to a beginner, but they leave "
      "the statistical fingerprint of the language untouched.";
  auto v = attacks::break_vigenere(classical::vigenere_encrypt(secret, "CRYPTO"));
  std::cout << "break_vigenere found key " << v.key << " (length " << v.key_length << ")\n";
  std::cout << "  first words: " << v.plaintext.substr(0, 60) << "...\n";
  return 0;
}
