#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

using llong = int64_t;
using ldouble = long double;
using pldouble = std::pair<ldouble, ldouble>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

ldouble solve(const ldouble &D, const std::vector<pldouble> &X, const ldouble &A) {
  ldouble gap = 0;
  REP(i, SIZE(X)) {
    gap = std::max(gap, X[i].first - sqrtl(2 * X[i].second * A) / A);
  }
  return gap + sqrtl(2 * D * A) / A;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    ldouble D, Ai;
    int N, A;
    std::cin >> D >> N >> A;

    std::vector<pldouble> X(N);
    REP(i, N) {
      std::cin >> X[i].first >> X[i].second;
    }
    while (N > 1 && X[N - 2].second > D) {
      N--;
    }
    if (N == 1 && X[0].second > D) {
      N--;
    } else if (N > 1) {
      X[N - 1].first = X[N - 2].first
          + ((D - X[N - 2].second) / (X[N - 1].second - X[N - 2].second)
              * (X[N - 1].first - X[N - 2].first));
      X[N - 1].second = D;
    }
    X.resize(N);

    printf("Case #%d:\n", t + 1);
    REP(i, A) {
      std::cin >> Ai;
      printf("%.6Lf\n", solve(D, X, Ai));
    }
  }

  return 0;
}
