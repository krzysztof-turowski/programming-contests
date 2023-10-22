#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using ldouble = long double;
using vint = std::vector<int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const int INF = 1000000000;

int triangle(const int &a) {
  return a * (a + 1) / 2;
}

int solve(const int &N, const int &M, const int &K) {
  vint X((N + 1) * (M + 1), INF);
  FOR(i, 1, N) FOR(j, 1, M) {
    if (i == 1 || j == 1) {
      X[i * j] = std::min(X[i * j], std::max(i, j));
    } else {
      X[i * j] = std::min(X[i * j], 2 * (i + j) - 4);
    }
  }
  FORD(i, N * M - 1, 0) {
    X[i] = std::min(X[i], X[i + 1]);
  }
  int best = N * M;
  REP(a1, N + 1) REP(b1, N + 1) REP(a2, N + 1) REP(b2, N + 1) {
    if (a1 + b1 >= N || a2 + b2 >= N || a1 + a2 >= M || b1 + b2 >= M) {
      continue;
    }
    int needed = K + triangle(a1) + triangle(b1) + triangle(a2) + triangle(b2);
    if (needed > N * M) {
      continue;
    }
    best = std::min(best, X[needed] - a1 - a2 - b1 - b2);
  }
  return best;
}

int main() {
  int T;
  std::cin >> T;

  REP(t, T) {
    int N, M, K;
    std::cin >> N >> M >> K;
    if (N > M) {
      std::swap(N, M);
    }
    printf("Case #%d: %d\n", t + 1, solve(N, M, K));
  }
  return 0;
}
