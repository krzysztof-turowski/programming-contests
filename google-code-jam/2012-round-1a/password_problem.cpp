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

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int A, B;
    std::cin >> A >> B;

    double P[A], X[A + 1], E0 = B + 2;
    REP(i, A) {
      std::cin >> P[i];
    }
    X[0] = 1;
    REP(i, A) {
      X[i + 1] = X[i] * P[i];
    }
    REP(i, A + 1) {
      double E = X[A - i] * (i + B - A + i + 1) + (1 - X[A - i]) * (i + B - A + i + 1 + B + 1);
      if (E < E0) {
        E0 = E;
      }
    }
    printf("Case #%d: %.6lf\n", t + 1, E0);
  }

  return 0;
}
