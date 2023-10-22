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
using vdouble = std::vector<double>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

double solve() {
  int N, K;
  double p;
  std::cin >> N >> K >> p;

  vdouble probability(K + 1, 0), win(N + 1), prizes(N + 1);
  probability[0] = 1;
  FOR(i, 1, N) {
    FORD(j, K, 1) {
      probability[j] = probability[j - 1] * p + probability[j] * (1 - p);
    }
    win[i] = probability[K];
  }
  FOR(i, 1, N) {
    FOR(j, 1, i) {
      double value = win[j] + prizes[i - j];
      if (prizes[i] < value)
        prizes[i] = value;
    }
  }
  return prizes[N];
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %.7lf\n", t + 1, solve());
  }
  return 0;
}
