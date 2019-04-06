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
#define INFL 1000000000000000000LL

bool check(const int *Y, const int &A) {
  REP(i, A) FOR(j, i + 1, Y[i] - 1)
    if (Y[j] > Y[i])
      return false;
  return true;
}

int main() {
  int T, MAX = 10000000;
  std::cin >> T;

  REP(t, T) {
    int A;
    std::cin >> A, A--;

    int Y[A], X[A + 1], Z[A + 1];
    REP(i, A)
      std::cin >> Y[i], Y[i]--;

    if (check(Y, A)) {
      X[A] = MAX, Z[A] = -1;
      FORD(i, A - 1, 0)
        Z[i] = Z[Y[i]] + 1, X[i] = X[Y[i]] - 1 - Z[i] * (Y[i] - i);

      printf("Case #%d: ", t + 1);
      REP(i, A + 1)
        printf("%d ", X[i]);
      puts("");
    } else {
      printf("Case #%d: Impossible\n", t + 1);
    }
  }

  return 0;
}
