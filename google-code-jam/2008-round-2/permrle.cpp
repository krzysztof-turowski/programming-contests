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

using llong = int64_t;
using ldouble = long double;
using vint = std::vector<int>;
using graph = std::vector<vint>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const int INF = 1000000000;

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
