# CryptoLab++

> Educational cryptography library, cryptanalysis lab, and hybrid post-quantum messenger, written in modern C++20.

![CI](https://github.com/<your-username>/cryptolab-cpp/actions/workflows/ci.yml/badge.svg)

**⚠️ The `core` library is for learning only. It is not constant-time and must not be used to protect real data.** The messenger layer uses audited libraries (libsodium, liboqs).

## Layers

| Layer | Purpose | Status |
|---|---|---|
| `core` | From-scratch classical, symmetric, public-key, hash and signature implementations | 🚧 Phase 1 |
| `attacks` | Cryptanalysis lab: break weak ciphers and flawed constructions | ⏳ Planned |
| `secure-msg` | Hybrid (X25519 + ML-KEM) end-to-end encrypted messenger | ⏳ Planned |

See [docs/ROADMAP.md](docs/ROADMAP.md) for the phase plan.

## Build

```bash
cmake --preset release
cmake --build --preset release --parallel
ctest --preset release
```

Sanitizer build (ASan + UBSan, warnings as errors):

```bash
cmake --preset asan && cmake --build --preset asan && ctest --preset asan
```

Requires CMake ≥ 3.20 and a C++20 compiler (GCC 11+, Clang 14+). GoogleTest is fetched automatically.

## Project layout

```
include/cryptolab/   public headers
src/                 implementations
tests/               GoogleTest unit tests (official test vectors)
docs/                per-algorithm notes, roadmap, threat model
cmake/               build helpers
```

## Background

Built on the topics of NPTEL *Theory and Practice of Modern Cryptography* (IIT Kharagpur, 2026).

## License

MIT
