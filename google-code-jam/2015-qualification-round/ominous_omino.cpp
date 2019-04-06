#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

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
typedef std::vector<ldouble> vldouble;
typedef std::vector<std::string> vstring;
typedef std::vector<llong> vllong;
typedef std::vector<vint> graph;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ADD_EDGE(g, u, v) g[u].push_back(v), g[v].push_back(u)

#define ST first
#define ND second
#define INF 1000000000LL
#define EPS 1e-5

bool solve(const int &X, const int &R, const int &C) {
  if (X > 6 || X > R || (X + 1) / 2 > C || (R * C) % X)
    return true;
  if (X == 4 && C == 2)
    return true;
  if (X == 5 && C == 3 && R == 5)
    return true;
  if (X == 6 && C == 3)
    return true;

  return false;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int X, R, C;
    std::cin >> X >> R >> C;

    printf("Case #%d: %s\n",
        t + 1, solve(X, std::max(R, C), std::min(R, C)) ? "RICHARD" : "GABRIEL");
  }

  return 0;
}
