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

int V[4][4] = { { 1, 2, 3, 4 }, { 2, -1, 4, -3 }, { 3, -4, -1, 2 }, { 4, 3, -2, -1 } };

int value(const int &X, const char &c) {
  int Y = c == 'i' ? 1 : (c == 'j' ? 2 : 3);
  return X > 0 ? V[X - 1][Y] : -V[-X - 1][Y];
}

bool solve(const std::string &W, const int &L) {
  int a = 2, q = 1;
  REP(i, SIZE(W)) {
    q = value(q, W[i]);
    if (a == q)
      a++, q = 1;
  }
  return a == 5 && q == 1;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int L;
    llong X;
    std::string word = "", W;

    std::cin >> L >> X >> W;
    if (X >= 12LL)
      X = X % 4LL + 12LL;
    REP(i, X)
      word += W;

    printf("Case #%d: %s\n", t + 1, solve(word, L) ? "YES" : "NO");
  }

  return 0;
}
