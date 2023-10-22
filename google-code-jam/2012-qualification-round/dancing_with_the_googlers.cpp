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
    int n, s, p, v;
    std::cin >> n >> s >> p;

    int score = 0;
    REP(j, n) {
      std::cin >> v;
      if (v / 3 + (v % 3 > 0) >= p) {
        score++;
      } else if (v / 3 + (v % 3) / 2 + 1 == p && v / 3 >= 1 - (v % 3) / 2 && s > 0) {
        score++, s--;
      }
    }
    printf("Case #%d: %d\n", t + 1, score);
  }

  return 0;
}
