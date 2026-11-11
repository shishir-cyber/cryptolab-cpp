# Workflow

- One feature per branch (`feat/aes-key-expansion`), one PR per feature.
- Conventional commits: `feat(aes): ...`, `test(rsa): ...`, `docs(des): ...`, `ci: ...`.
- Run `clang-format -i` on changed files; build with the `asan` preset before opening a PR.
- Every algorithm needs official test vectors (NIST CAVP / RFC) where available.
