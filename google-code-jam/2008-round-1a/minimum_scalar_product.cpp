#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int A;
    std::cin >> A;

    llong X[A], Y[A];
    REP(i, A) {
      std::cin >> X[i];
    }
    REP(i, A) {
      std::cin >> Y[i];
    }
    std::sort(X, X + A), std::sort(Y, Y + A, std::greater<int>());

    llong E = 0;
    REP(i, A) {
      E += X[i] * Y[i];
    }
    printf("Case #%d: %lld\n", t + 1, E);
  }
  return 0;
}
