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

const int MAX = 100000;

long double solve(const long double &p) {
  long double out = 0;
  REP(i, MAX) {
    out += 1.0 - pow(1 - pow(1 - p, i), 20);
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    long double p;
    std::cin >> p;
    printf("Case #%d: %.6Lf\n", t + 1, solve(p));
  }
  return 0;
}
