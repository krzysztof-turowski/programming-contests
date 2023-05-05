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

typedef int64_t llong;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

llong solve() {
  int N;
  std::cin >> N;

  llong P;
  std::cin >> P;
  std::vector<llong> B(N);
  REP(i, N) {
    std::cin >> B[i];
  }
  llong sum = 0, out = 0;
  int low = 0;
  REP(high, N) {
    sum += B[high];
    while (sum > P) {
      sum -= B[low];
      low++;
    }
    out += (high + 1 - low);
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %lld\n", t + 1, solve());
  }
  return 0;
}
