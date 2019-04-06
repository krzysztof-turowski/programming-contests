#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

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
#define PART(c, k) c.begin(), c.begin() + (k)

#define ST first
#define ND second
#define INF 1000000000LL

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int A, B;
    std::cin >> A >> B;

    double P[A], X[A + 1], E0 = B + 2;
    REP(i, A)
      std::cin >> P[i];

    X[0] = 1;
    REP(i, A)
      X[i + 1] = X[i] * P[i];
    REP(i, A + 1) {
      double E = X[A - i] * (i + B - A + i + 1) + (1 - X[A - i]) * (i + B - A + i + 1 + B + 1);
      if (E < E0)
        E0 = E;
    }

    printf("Case #%d: %.6lf\n", t + 1, E0);
  }

  return 0;
}
