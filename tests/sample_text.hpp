#pragma once
#include <string_view>

// A few hundred letters of ordinary English, used by the frequency-analysis attack tests.
inline constexpr std::string_view kSampleEnglish =
    "Cryptography is the practice of securing communication in the presence of adversaries. "
    "For many centuries people protected their messages with simple substitutions, shifting "
    "every letter of the alphabet by a fixed amount or replacing each letter with another one "
    "according to a secret rule. These ciphers look very strong to a beginner, but they leave "
    "the statistical fingerprint of the language untouched. In English the letter e appears far "
    "more often than the letter z, and an attacker who counts the letters of a long message can "
    "often recover the secret key without trying every possibility. Modern ciphers were designed "
    "specifically to remove such patterns, so that the ciphertext looks like random noise to "
    "anyone who does not hold the key. Understanding how the old systems fail is the best way to "
    "understand why the new ones are built the way they are, and it teaches the habit of thinking "
    "like an attacker, which is the most important skill in security engineering.";
