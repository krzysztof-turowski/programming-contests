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
using vllong = std::vector<llong>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

class element {
 public:
  llong time, endtime;

  explicit element(const llong &time) : time(time), endtime(time) { }
  element(const llong &time, const llong &endtime) : time(time), endtime(endtime) { }
};

llong solve() {
  llong L, N, M, D;
  std::cin >> L >> N >> M >> D;

  vllong W(N);
  REP(i, N) {
    std::cin >> W[i];
  }
  std::sort(W.begin(), W.end());

  auto compare = [](element a, element b) { return a.endtime > b.endtime; };
  std::priority_queue<element, std::vector<element>, decltype(compare)> Q(compare);
  REP(i, std::min(L, N)) {
    Q.emplace(W[i]);
  }
  vllong washed(L), dryed(std::min(M, L), 0L);
  REP(i, L) {
    auto machine = Q.top();
    dryed[i % M] = std::max(dryed[i % M], machine.endtime) + D;
    Q.pop(), Q.emplace(machine.time, machine.endtime + machine.time);
  }
  return *std::max_element(dryed.begin(), dryed.end());
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %lld\n", t + 1, solve());
  }
  return 0;
}
