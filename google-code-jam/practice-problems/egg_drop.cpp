#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

typedef int64_t llong;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int main() {
  const llong D = 2000000000L, W = 31L, MAXINT = 1L << 32;

  llong length = sqrt(D), width = W, V[length][width];
  REP(i, width) {
    V[0][i] = 1;
  }
  FOR(i, 1, length - 1) {
    V[i][0] = i + 1;
    FOR(j, 1, width - 1) {
      V[i][j] = V[i - 1][j - 1] + V[i - 1][j] + 1;
      if (!V[i][j - 1] || !V[i - 1][j] || V[i][j] > MAXINT) {
        V[i][j] = 0;
      }
    }
  }

  int T;
  std::cin >> T;
  REP(t, T) {
    llong F0, D0, B0, D1, F, D = 1, B = 2;
    std::cin >> F0 >> D0 >> B0, D1 = D0, B0 = std::min(D0, B0);
    F = (B0 == 1) ? D0 : (D0 > length || B0 > width ? 0 : V[D0 - 1][B0 - 1]);
    while (D < D0) {
      llong d = (D + D0) / 2;
      if (d > length || std::min(d, B0) > width || !V[d - 1][std::min(d, B0) - 1]
          || F0 <= V[d - 1][std::min(d, B0) - 1]) {
        D0 = d;
      } else {
        D = d + 1;
      }
    }
    if (F0 <= D1) {
      B = 1;
    } else {
      while (B < B0) {
        llong b = (B + B0) / 2;
        if (D1 > length || b > width || !V[D1 - 1][b - 1] || F0 <= V[D1 - 1][b - 1]) {
          B0 = b;
        } else {
          B = b + 1;
        }
      }
    }
    printf("Case #%d: %lld %lld %lld\n", t + 1, F ? F : -1, D, B);
  }

  return 0;
}
