#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

void dfs(
    const int &v, const int &index, const std::vector<std::vector<int>> &G,
    std::vector<int> &visited) {
  visited[v] = index;
  for (const auto &u : G[v]) {
    if (visited[u] == -1) {
      dfs(u, index, G, visited);
    }
  }
}

std::set<int> knapsack(const std::vector<int> &S, const int &value) {
  std::vector<std::vector<int>> T(S.size() + 1, std::vector<int>(value + 1));
  T[0][0] = true;
  for (int i = 0; i < S.size(); i++) {
    for (int j = 0; j < std::min(S[i], value + 1); j++) {
      T[i + 1][j] = T[i][j];
    }
    for (int j = S[i]; j <= value; j++) {
      T[i + 1][j] = (T[i][j] | T[i][j - S[i]]);
    }
  }
  int best = value;
  while (!T[S.size()][best]) {
    best--;
  }
  std::set<int> out;
  for (int i = S.size() - 1; i >= 0; i--) {
    if (best < S[i]) {
      continue;
    }
    if (T[i][best - S[i]]) {
      out.insert(i), best -= S[i];
    }
  }
  return out;
}

std::string solve(const std::vector<std::vector<int>> &G) {
  std::vector<int> visited(G.size(), -1);
  int count = 0;
  for (int i = 0; i < G.size(); i++) {
    if (visited[i] == -1) {
      dfs(i, count++, G, visited);
    }
  }
  std::vector<int> S(count);
  for (int i = 0; i < G.size(); i++) {
    S[visited[i]]++;
  }
  std::set<int> V = knapsack(S, G.size() / 2);
  std::string out(G.size(), '0');
  int X = 0;
  for (int i = 0; i < G.size(); i++) {
    if (V.count(visited[i])) {
      out[i] = '1';
      X++;
    }
  }
  return out;
}

int main() {
  int T, N, M;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int X, Y;
    std::cin >> N >> M;
    std::vector<std::vector<int>> G(N);
    for (int i = 0; i < M; i++) {
      std::cin >> X >> Y;
      for (int j = X - 1, k = Y - 1; j < k; j++, k--) {
        G[j].push_back(k), G[k].push_back(j);
      }
    }
    printf("Case #%d: %s\n", t + 1, solve(G).c_str());
  }
  return 0;
}
