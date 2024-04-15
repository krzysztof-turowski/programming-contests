#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const int64 MOD = 1000000007;
const int MAX = 100001;

std::vector<int64> F, F_inv;

std::vector<int64> factorial(int size) {
  F.resize(size);
  F[0] = F[1] = 1;
  FOR(i, 2, size - 1) {
    F[i] = (i * F[i - 1]) % MOD;
  }
  return F;
}

std::pair<int64, int64> extended_gcd(int64 a, int64 b) {
  if (a == 0) {
    assert(b == 1);
    return std::make_pair(0LL, 1LL);
  }
  auto [y, x] = extended_gcd(b % a, a);
  return std::make_pair(x - (b / a) * y, y);
}

std::vector<int64> inverse_factorial(int size) {
  F_inv.resize(size);
  REP(i, size) {
    F_inv[i] = (extended_gcd(F[i], MOD).first + MOD) % MOD;
  }
  return F_inv;
}

int64 recurse(std::vector<int> &S, int i, int j, int shift) {
  if (i > j) {
    return 1;
  }
  int k = std::find(S.begin() + i, S.begin() + j + 1, shift) - S.begin();
  if (k == j + 1) {
    return 0;
  }
  auto values = (recurse(S, i, k - 1, shift + 1) * recurse(S, k + 1, j, shift)) % MOD;
  auto binomial = (((F[j - i] * F_inv[j - k]) % MOD) * F_inv[k - i]) % MOD;
  return (binomial * values) % MOD;
}

int64 solve(std::vector<int> &S) {
  std::reverse(S.begin(), S.end());
  return recurse(S, 0, S.size() - 1, 1);
}

int main() {
  factorial(MAX + 1), inverse_factorial(MAX + 1);
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;
    std::vector<int> S(N);
    REP(i, N) {
      std::cin >> S[i];
    }
    printf("Case #%d: %lld\n", t + 1, solve(S));
  }
  return 0;
}
