#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

typedef int64_t llong;

int MAX = 64, MOD = 1000000007;

std::vector<int> F(MAX), invF(MAX), D(1 << 21);

inline int code(int i, int j, int ops_left, char need, bool full) {
  return (i << 15) | (j << 9) | (ops_left << 3) | (need << 1) | full;
}

llong modpow(llong base, llong exponent, llong modulus) {
  base %= modulus;
  llong out = 1LL;
  while (exponent > 0) {
    if (exponent & 1) {
      out = (out * base) % modulus;
    }
    base = (base * base) % modulus;
    exponent >>= 1;
  }
  return out;
}

void compute_F() {
  F[0] = invF[0] = 1;
  FOR(i, 1, MAX - 1) {
    F[i] = ((llong) F[i - 1] * i) % MOD;
  }
  FOR(i, 1, MAX - 1) {
    invF[i] = modpow(F[i], MOD - 2, MOD);
  }
}

int recurse(
    const std::string &S, int i, int j, int ops_left, char need, bool full) {
  if (i > j) {
    return !need && !ops_left;
  }
  int key = code(i, j, ops_left, need, full);
  if (D[key] >= 0) {
    return D[key];
  }
  int out = recurse(S, i + 1, j, ops_left, S[i] == need ? 0 : need, true);
  for (int k = i + 1; k <= j; k++) {
    if (k == j && !full) {
      continue;
    }
    for (int ops = 0; ops < std::min(ops_left, k - i); ops++) {
      for (int c = 1; c <= 2; c++) {
        llong f = ((llong) invF[ops + 1] * F[ops]) % MOD;
        int left = recurse(S, i, k, ops, c, false);
        int right = recurse(
            S, k + 1, j, ops_left - ops - 1, need == c ? 0 : need, true);
        out = (out + (((f * left) % MOD) * right) % MOD) % MOD;
      }
    }
  }
  return D[key] = out;
}

int solve(std::string &S) {
  std::fill(D.begin(), D.end(), -1);
  int N = S.size();
  for (int i = 0; i < N; i++) {
    S[i] -= ('a' - 1);
  }
  int out = 0;
  for (int ops = 0; ops < N; ops++) {
    out = (out + (llong) F[ops] * recurse(S, 0, N - 1, ops, 0, true)) % MOD;
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  compute_F();
  for (int t = 0; t < T; t++) {
    std::string S;
    std::cin >> S;
    printf("Case #%d: %d\n", t + 1, solve(S));
  }
  return 0;
}
