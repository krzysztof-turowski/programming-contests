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

int solve(const vint &P, const int &maxP) {
  int out = INF;
  FOR(k, 1, maxP) {
    int A = 0;
    FOREACH(it, P)
      A += (*it / k) - !(*it % k);
    if (A + k < out)
      out = A + k;
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
    REP(i, D)
      std::cin >> P[i];

    printf("Case #%d: %d\n", t + 1, solve(P, *max_element(ALL(P))));
  }

  return 0;
}
