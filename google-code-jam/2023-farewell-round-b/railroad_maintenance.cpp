#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

typedef std::vector<int> vint;
typedef std::vector<vint> graph;

#define REP(i, n) for (int i = 0; i < (n); ++i)
#define ADD_EDGE(g, u, v) g[u].push_back(v), g[v].push_back(u)

int get_articulation_points(
    int v, int d, int N, const graph &G, vint &parent, vint &depth, vint &low) {
  depth[v] = low[v] = d;
  int children = 0, is_articulation = false, out = 0;
  for (const auto &u : G[v]) {
    if (depth[u] == 0) {
      parent[u] = v, children++;
      out += get_articulation_points(u, d + 1, N, G, parent, depth, low);
      if (low[u] >= depth[v]) {
        is_articulation = true;
      }
      low[v] = std::min(low[v], low[u]);
    } else if (u != parent[v]) {
      low[v] = std::min(low[v], depth[u]);
    }
  }
  if (v >= N && ((parent[v] != -1 && is_articulation) || (parent[v] == -1 && children > 1))) {
    out++;
  }
  return out;
}

int solve(const int &N, const int &L, const std::vector<vint> &S) {
  graph G(N + L);
  REP(i, L) {
    for (const auto &v : S[i]) {
      ADD_EDGE(G, v - 1, N + i);
    }
  }
  vint parent(G.size(), -1), depth(G.size(), 0), low(G.size(), 0);
  return get_articulation_points(0, 1, N, G, parent, depth, low);
}

int main() {
  int T;
  std::cin >> T;

  REP(t, T) {
    int N, L;
    std::cin >> N >> L;
    std::vector<std::vector<int>> S(L);
    REP(i, L) {
      int size;
      std::cin >> size;
      S[i].resize(size);
      REP(j, size) {
        std::cin >> S[i][j];
      }
    }
    printf("Case #%d: %d\n", t + 1, solve(N, L, S)), fflush(stdin);
  }
  return 0;
}
