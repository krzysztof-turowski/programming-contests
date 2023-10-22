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

const llong INF = 1000000000LL;

llong gcd(const llong &P, const llong &Q) {
  return P == 0 ? Q : gcd(Q % P, P);
}

int solve(llong &P, llong &Q) {
  llong X = gcd(P, Q);
  P /= X, Q /= X;

  bool possible = false;
  FOR(i, 1, 40) {
    if (Q == (1ULL << i)) {
      possible = true;
    }
  }

  if (possible) {
    FOR(i, 1, 40) {
      if (Q <= P * (1ULL << i)) {
        return i;
      }
    }
  }
  return INF;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    llong P, Q;
    scanf("%llu/%llu", &P, &Q);

    printf("Case #%d: ", t + 1);
    int out = solve(P, Q);
    if (out == INF) {
      std::cout << "impossible" << std::endl;
    } else {
      std::cout << out << std::endl;
    }
  }

  return 0;
}
