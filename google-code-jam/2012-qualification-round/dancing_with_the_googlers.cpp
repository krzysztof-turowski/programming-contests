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
    int n, s, p, v;
    std::cin >> n >> s >> p;

    int score = 0;
    REP(j, n) {
      std::cin >> v;
      if (v / 3 + (v % 3 > 0) >= p) {
        score++;
      } else if (v / 3 + (v % 3) / 2 + 1 == p && v / 3 >= 1 - (v % 3) / 2 && s > 0) {
        score++, s--;
      }
    }
    printf("Case #%d: %d\n", t + 1, score);
  }

  return 0;
}
