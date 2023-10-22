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

bool solve(const int &X, const int &R, const int &C) {
  if (X > 6 || X > R || (X + 1) / 2 > C || (R * C) % X) {
    return true;
  }
  if (X == 4 && C == 2) {
    return true;
  }
  if (X == 5 && C == 3 && R == 5) {
    return true;
  }
  if (X == 6 && C == 3) {
    return true;
  }
  return false;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int X, R, C;
    std::cin >> X >> R >> C;

    printf("Case #%d: %s\n",
        t + 1, solve(X, std::max(R, C), std::min(R, C)) ? "RICHARD" : "GABRIEL");
  }

  return 0;
}
