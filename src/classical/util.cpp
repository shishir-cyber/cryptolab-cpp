#include "cryptolab/classical/util.hpp"

namespace cryptolab::classical {

int gcd(int a, int b) {
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  while (b != 0) {
    const int t = a % b;
    a = b;
    b = t;
  }
  return a;
}

int mod_inverse(int a, int m) {
  // Extended Euclid: track coefficients s such that s*a == r (mod m).
  int old_r = mod(a, m), r = m;
  int old_s = 1, s = 0;
  while (r != 0) {
    const int q = old_r / r;
    int t = old_r - q * r;
    old_r = r;
    r = t;
    t = old_s - q * s;
    old_s = s;
    s = t;
  }
  if (old_r != 1) return -1;  // gcd(a, m) != 1 -> no inverse
  return mod(old_s, m);
}

}  // namespace cryptolab::classical
