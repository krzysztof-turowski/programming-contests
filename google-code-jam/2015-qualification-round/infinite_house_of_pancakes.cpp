#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using ldouble = long double;
using pint = std::pair<int, int>;
using vint = std::vector<int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const int INF = 1000000000;

int solve(const vint &P, const int &maxP) {
  int out = INF;
  FOR(k, 1, maxP) {
    int A = 0;
    for (auto it : P) {
      A += (it / k) - !(it % k);
    }
    if (A + k < out) {
      out = A + k;
    }
  }

  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int D;
    std::cin >> D;
    vint P(D);
    REP(i, D) {
      std::cin >> P[i];
    }
    printf("Case #%d: %d\n", t + 1, solve(P, *std::max_element(P.begin(), P.end())));
  }

  return 0;
}
