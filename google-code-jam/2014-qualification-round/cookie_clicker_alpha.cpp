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
#include <cassert>

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
#define PB push_back
#define INF 1000000000LL
#define EPS 1e-5

ldouble compute(int n, const ldouble &C, const ldouble &F, const ldouble &X) {
  if (n < 0)
    n = 0;
  ldouble Ti = 0;
  REP(i, n)
    Ti += 1 / (2 + i * F);
  return X / (2 + n * F) + C * Ti;
}

void check(const ldouble &minus, const ldouble &out, const ldouble &plus) {
  assert(out <= minus && out <= plus);
}

int main() {
  int N;
  std::cin >> N;
  REP(t, N) {
    ldouble C, F, X;
    std::cin >> C >> F >> X;

    int n = std::max((X * F - 2) / (F * C) - 1, 0.0L);
    ldouble minus = compute(n - 1, C, F, X);
    ldouble out = compute(n, C, F, X);
    ldouble plus = compute(n + 1, C, F, X);
    if (out > plus) {
      n++, minus = out, out = plus, check(minus, out, compute(n + 1, C, F, X));
    } else if (out > minus) {
      n--, plus = out, out = minus, check(compute(n - 1, C, F, X), out, plus);
    }
    printf("Case #%d: %.7Lf\n", t + 1, out);
  }

  return 0;
}
