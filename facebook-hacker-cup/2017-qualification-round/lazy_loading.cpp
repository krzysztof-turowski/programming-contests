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

bool remove(std::deque<int> &Q) {
  int W = Q.back(), K = 1;
  Q.pop_back();
  while (W * K < 50 && !Q.empty()) {
    K++, Q.pop_front();
  }
  return W * K >= 50;
}

int main() {
  int T, N;
  std::cin >> T;
  REP(i, T) {
    std::cin >> N;
    std::deque<int> Q(N);
    REP(j, N) {
      std::cin >> Q[j];
    }
    std::sort(Q.begin(), Q.end());
    int out = 0;
    while (!Q.empty()) {
      out += remove(Q);
    }
    printf("Case #%d: %d\n", i + 1, out);
  }
  return 0;
}
