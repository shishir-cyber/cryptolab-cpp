# Phase 1: Classical ciphers and their attacks

NPTEL Week 1 (and the Hill cipher from Week 2). All code lives in `classical/` and `attacks/`.
**Educational only. These ciphers are trivially breakable, which is the point.**

| Cipher | Key | Why it breaks |
|---|---|---|
| Shift / Caesar | one number 0-25 | Only 26 keys: try them all |
| Affine | (a, b), gcd(a,26)=1 | Only 12 x 26 = 312 keys: try them all |
| Vigenere | repeating word | Each key position is a separate shift cipher; the Index of Coincidence reveals the key length |
| Playfair | 5x5 square | Hides single-letter frequencies but not digraph frequencies (not implemented as an attack yet) |
| Hill (2x2) | 2x2 matrix mod 26 | Linear: a few known plaintext pairs give the key (attack TODO) |
| Columnar transposition | keyword | Letters are not changed, only moved: anagramming attacks (TODO) |

## Tools used by the attacks

- **Chi-squared score**: how far a text's letter counts are from normal English. Lower is better.
- **Index of Coincidence (IoC)**: chance that two random letters of a text match. English is about 0.067, random letters about 0.038.
- **Extended Euclidean Algorithm**: finds modular inverses (needed to decrypt Affine and Hill).

## Possible extensions
- Kasiski examination as a second key-length estimator
- Known-plaintext attack on Hill
- Hill-climbing attack on Playfair and substitution ciphers using bigram/quadgram scores
- A small CLI demo (`cryptolab-cli caesar --encrypt ...`)
