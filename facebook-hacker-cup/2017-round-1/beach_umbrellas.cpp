#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using llong = int64_t;

const llong MOD = 1000000007;

llong power(const llong &value, const llong &exponent, const llong &mod) {
  if (exponent == 1) {
    return value;
  }
  llong half = power(value, exponent / 2, mod), half_square = (half * half) % MOD;
  return exponent % 2 ? (half_square * value) % MOD : half_square;
}

llong solve(const std::vector<llong> &R, const llong &M) {
  if (R.size() == 1) {
    return M;
  }
  llong out = 0, inverse = power(R.size() * (R.size() - 1), MOD - 2, MOD);
  std::map<llong, int> L_values;
  llong R_sum = 0;
  for (const auto &r : R) {
    R_sum += r;
  }
  for (int i = 0; i < R.size(); i++) {
    for (int j = i + 1; j < R.size(); j++) {
      llong L = M - 1 + R[i] + R[j] - 2 * R_sum;
      if (L >= 0) {
        L_values[L]++;
      }
    }
  }
  for (const auto &l : L_values) {
    if (l.first > 0) {
      llong value = 1;
      for (int i = 1; i <= R.size(); i++) {
        value = (value * (l.first + i)) % MOD;
      }
      value = (value * l.second) % MOD;
      value = (value * inverse) % MOD;
      out = (out + value) % MOD;
    } else {
      llong value = 1;
      for (int i = 1; i <= R.size() - 2; i++) {
        value = (value * i) % MOD;
      }
      value = (value * l.second) % MOD;
      out = (out + value) % MOD;
    }
  }
  return (2 * out) % MOD;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    llong N, M;
    std::cin >> N >> M;
    std::vector<llong> R(N);
    for (int i = 0; i < N; i++) {
      std::cin >> R[i];
    }
    printf("Case #%d: %lld\n", t + 1, solve(R, M));
  }
  return 0;
}
