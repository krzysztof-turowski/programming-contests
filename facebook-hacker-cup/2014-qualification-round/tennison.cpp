#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
  #define _USE_MATH_DEFINES
#endif

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

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef vint::iterator vit;
typedef std::vector<double> vdouble;
typedef vdouble::iterator vdit;
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
#define INF 1000000000
#define INFL 1000000000000000000LL
#define MOD 1000000007L
#define EPS 1e-5

double solve() {
  const int VALUES = 1000;
  int K, changeI[2];
  double win[2], start, change[2], step[2];

  std::cin >> K >> win[0] >> win[1] >> start >> change[0] >> step[0] >> change[1] >> step[1];
  changeI[0] = change[0] * VALUES + 1e-6, changeI[1] = change[1] * VALUES + 1e-6;

  std::vector<std::vector<vdouble> > V(K + 1);
  REP(i, K + 1) {
    V[i].resize(K + 1);
    REP(j, K + 1)
      V[i][j].resize(VALUES + 1, -1);
  }

  REP(i, K + 1) REP(j, VALUES + 1)
    V[i][K][j] = 0, V[K][i][j] = 1;

  FORD(i, K - 1, 0) FORD(j, K - 1, 0) REP(k, VALUES + 1) {
    double p = static_cast<double>(k) / VALUES;
    V[i][j][k] = (p * win[0] + (1 - p) * win[1])
        * step[0] * V[i + 1][j][std::min(k + changeI[0], VALUES)];
    V[i][j][k] += (p * win[0] + (1 - p) * win[1]) * (1 - step[0]) * V[i + 1][j][k];
    V[i][j][k] += (p * (1 - win[0]) + (1 - p) * (1 - win[1])) * step[1]
        * V[i][j + 1][std::max(k - changeI[1], 0)];
    V[i][j][k] += (p * (1 - win[0]) + (1 - p) * (1 - win[1])) * (1 - step[1]) * V[i][j + 1][k];
  }

  return V[0][0][static_cast<int>(start * VALUES + 1e-6)];
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %.6lf\n", t + 1, solve());

  return 0;
}
