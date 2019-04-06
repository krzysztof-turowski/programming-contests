#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ST first
#define ND second
#define INF 1000000000LL

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int A;
    std::cin >> A;

    llong X[A], Y[A];
    REP(i, A)
      std::cin >> X[i];
    REP(i, A)
      std::cin >> Y[i];

    std::sort(X, X + A), std::sort(Y, Y + A, std::greater<int>());

    llong E = 0;
    REP(i, A)
      E += X[i] * Y[i];

    printf("Case #%d: %lld\n", t + 1, E);
  }

  return 0;
}
