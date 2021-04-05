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

const graph build_graph(const int &K, const std::string &S, const int &last) {
  graph G(K, vint(K, 0));
  for (int x = 0; x < K; x++) {
    for (int y = 0; y < K; y++) {
      if (x == y) {
        continue;
      }
      if (x == last) {
        for (int i = x, j = y + K; j < S.size(); i += K, j += K) {
          G[x][y] += (S[i] != S[j]);
        }
      } else {
        for (int i = x, j = y; i < S.size() && j < S.size(); i += K, j += K) {
          G[x][y] += (S[i] != S[j]);
        }
      }
    }
  }
  return G;
}

int solve_graph(const graph &G, const int &K) {
  std::vector<vint> DP(1 << K, vint(K, INF));
  for (int x = 0; x < K; x++) {
    DP[1 << x][x] = G[x][0];
  }
  for (int A = 0; A < (1 << K); A++) {
    for (int x = 0; x < K; x++) {
      for (int y = 0; y < K; y++) {
        if (!((1 << x) & A) || ((1 << y) & A)) {
          continue;
        }
        int B = A | (1 << y);
        DP[B][y] = std::min(DP[B][y], G[y][x] + DP[A][x]);
      }
    }
  }
  return DP[(1 << K) - 1][0] + 1;
}

int solve(const int &K, const std::string &S) {
  int out = S.size();
  for (int last = 0; last < K; last++) {
    auto G = build_graph(K, S, last);
    out = std::min(out, solve_graph(G, K));
  }
  return out;
}

int main() {
  int T, K;
  std::string S;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> K, std::cin.ignore(256, '\n');
    std::cin >> S;
    printf("Case #%d: %d\n", t + 1, solve(K, S));
  }
  return 0;
}
