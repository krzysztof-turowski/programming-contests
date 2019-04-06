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

struct level {
  llong index, length, death;

  inline bool operator<(const struct level &a) const {
    return a.death * length < death * a.length;
  }
};

int main() {
  int N;
  std::cin >> N;

  REP(t, N) {
    int T;
    std::cin >> T;

    struct level levels[T];
    REP(i, T)
      levels[i].index = i, std::cin >> levels[i].length;
    REP(i, T)
      std::cin >> levels[i].death;

    std::stable_sort(levels, levels + T);

    printf("Case #%d: ", t + 1);
    REP(i, T)
      printf("%lld ", levels[i].index);
    puts("");
  }

  return 0;
}
