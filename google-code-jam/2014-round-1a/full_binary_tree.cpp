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
#define PB push_back
#define INF 1000000000LL
#define EPS 1e-5

int subtree(const graph &G, const int &N, const int &index, const int &parent) {
  if (SIZE(G[index]) <= 1)
    return 1;
  if (SIZE(G[index]) == 2 && parent >= 0)
    return 1;

  vint A;
  REP(i, SIZE(G[index]))
    if (G[index][i] != parent)
      A.push_back(subtree(G, N, G[index][i], index));

  std::sort(ALL(A), std::greater<int>());
  return A[0] + A[1] + 1;
}

int solve(const graph &G, const int &N) {
  int out = 0;
  REP(i, N) {
    out = std::max(out, subtree(G, N, i, -1));
    if (out == N)
      return N;
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N, u, v;
    std::cin >> N;

    graph G(N);
    REP(i, N - 1)
      std::cin >> u >> v, --u, --v, G[u].push_back(v), G[v].push_back(u);

    printf("Case #%d: ", t + 1);
    std::cout << N - solve(G, N) << std::endl;
  }

  return 0;
}
