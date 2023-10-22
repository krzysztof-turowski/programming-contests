#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using llong = int64_t;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

struct data {
  llong A, B, K;

  data(const llong &A, const llong &B, const llong &K) : A(A), B(B), K(K) { }

  bool operator<(const data &X) const {
    return A < X.A || (A == X.A && B < X.B) || (A == X.A && B == X.B && K < X.K);
  }
};

void gen(const int &a, const int &b, const int &k) {
  std::vector<int> K(k);
  REP(i, a) REP(j, b) {
    K[i & j]++;
  }
  std::cout << a << " " << b << ": ";
  REP(i, k) {
    std::cout << K[i] << " ";
  }
  std::cout << std::endl;
}

llong solve(const llong &A, const llong &B, const llong &K, std::map<data, llong> &M) {
  std::map<data, llong>::iterator it = M.find(data(A, B, K));
  if (it != M.end()) {
    return it->second;
  }
  if (A == 0 || B == 0 || K == 0) {
    return 0;
  }
  if (A == 1) {
    return B;
  }
  if (B == 1) {
    return A;
  }
  llong a = solve(A / 2, B / 2, K / 2, M);
  llong b = solve((A + 1) / 2, B / 2, (K + 1) / 2, M);
  llong c = solve(A / 2, (B + 1) / 2, (K + 1) / 2, M);
  llong d = solve((A + 1) / 2, (B + 1) / 2, (K + 1) / 2, M);
  return M[data(A, B, K)] = a + b + c + d;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    llong A, B, K;
    std::cin >> A >> B >> K;
    std::map<data, llong> M;

    printf("Case #%d: %llu\n", t + 1, solve(A, B, K, M));
  }

  return 0;
}
