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

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

bool calculate(const ldouble &percent, const ldouble &x, const ldouble &y) {
  if (x * x + y * y > 2500) {
    return false;
  }
  ldouble value = atan2(y, x) * 50 / M_PI;
  return value < 25 ? (25 - value < percent) : (125 - value < percent);
}

int main() {
  int T;
  ldouble percent, x, y;
  std::cin >> T;
  REP(i, T) {
    std::cin >> percent >> x >> y;
    printf("Case #%d: %s\n", i + 1, calculate(percent, x - 50, y - 50) ? "black" : "white");
  }
  return 0;
}
