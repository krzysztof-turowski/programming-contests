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

const llong MOD = 1000000007LL;

class element {
 public:
  llong X, H;

  element() : X(0), H(0) { }
  element(llong X, llong H) : X(X), H(H) { }
};

class group_element {
 public:
  llong count, sum, sum_sq, H;

  explicit group_element(const llong &H) : count(0), sum(0), sum_sq(0), H(H) { }

  void add(const llong &X) {
    count++, sum = (sum + X) % MOD, sum_sq = (sum_sq + (X * X) % MOD) % MOD;
  }

  llong confont(const llong &X) {
    llong B2 = count * (X * X % MOD) % MOD;
    llong AB = MOD - (2 * (X * sum % MOD) % MOD);
    return (B2 + sum_sq + AB) % MOD;
  }
};

llong solve() {
  int N;
  std::cin >> N;

  std::vector<element> W(N);
  REP(i, N) {
    std::cin >> W[i].X >> W[i].H;
  }
  auto compare = [](const element &a, const element &b) { return a.X < b.X; };
  std::sort(W.begin(), W.end(), compare);

  llong out = 0;
  std::list<group_element> L;
  REP(i, N) {
    while (!L.empty() && L.front().H < W[i].H)
      L.pop_front();
    if (!L.empty() && L.front().H == W[i].H) {
      out = (out + L.front().confont(W[i].X)) % MOD;
    } else {
      L.push_front(group_element(W[i].H));
    }
    L.front().add(W[i].X);
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
