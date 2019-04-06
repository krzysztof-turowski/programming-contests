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

llong solve_any(const vllong &M) {
  llong out = 0;
  REP(i, SIZE(M) - 1)
    out += std::max(M[i] - M[i + 1], 0L);

  return out;
}

llong solve_fixed(const vllong &M) {
  llong size = 0, out = 0;
  REP(i, SIZE(M) - 1)
    size = std::max(M[i] - M[i + 1], size);
  REP(i, SIZE(M) - 1)
    out += std::min(size, M[i]);

  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;

    vllong M(N);
    REP(i, N)
      std::cin >> M[i];

    printf("Case #%d: %lld %lld\n", t + 1, solve_any(M), solve_fixed(M));
  }

  return 0;
}
