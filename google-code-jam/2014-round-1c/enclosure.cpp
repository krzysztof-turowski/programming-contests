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

int triangle(const int &a) {
  return a * (a + 1) / 2;
}

int solve(const int &N, const int &M, const int &K) {
  vint X((N + 1) * (M + 1), INF);
  FOR(i, 1, N)
    FOR(j, 1, M)
      if (i == 1 || j == 1) {
        X[i * j] = std::min(X[i * j], std::max(i, j));
      } else {
        X[i * j] = std::min(X[i * j], 2 * (i + j) - 4);
      }
  FORD(i, N * M - 1, 0)
    X[i] = std::min(X[i], X[i + 1]);

  int best = N * M;
  REP(a1, N + 1) REP(b1, N + 1) REP(a2, N + 1) REP(b2, N + 1) {
    if (a1 + b1 >= N || a2 + b2 >= N || a1 + a2 >= M || b1 + b2 >= M)
      continue;

    int needed = K + triangle(a1) + triangle(b1) + triangle(a2) + triangle(b2);
    if (needed > N * M)
      continue;

    best = std::min(best, X[needed] - a1 - a2 - b1 - b2);
  }
  return best;
}

int main() {
  int T;
  std::cin >> T;

  REP(t, T) {
    int N, M, K;
    std::cin >> N >> M >> K;
    printf("Case #%d: ", t + 1);

    if (N > M)
      std::swap(N, M);
    std::cout << solve(N, M, K) << std::endl;
  }

  return 0;
}
