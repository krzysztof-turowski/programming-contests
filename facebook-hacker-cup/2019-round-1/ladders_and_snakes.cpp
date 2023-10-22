#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

using llong = int64_t;

const llong INF = 100000000000LL;

struct ladder {
  int X, A, B;
};

llong BFS(
    const std::vector<std::vector<llong>> &G, const int &s, const int &t,
    std::vector<int> &parent) {
  std::vector<bool> visited(G.size(), false);
  std::queue<int> Q;
  Q.push(s);
  visited[s] = true, parent[s] = -1;
  while (!Q.empty()) {
    int u = Q.front();
    Q.pop();

    for (int v = 0; v < G.size(); v++) {
      if (!visited[v] && G[u][v] > 0) {
        Q.push(v), visited[v] = true, parent[v] = u;
      }
    }
  }
  return visited[t];
}

void DFS(const std::vector<std::vector<llong>> &G, const int &s, std::vector<bool> &visited) {
  visited[s] = true;
  for (int i = 0; i < G.size(); i++) {
    if (G[s][i] > 0 && !visited[i]) {
      DFS(G, i, visited);
    }
  }
}

llong min_cut(const std::vector<std::vector<llong>> &G) {
  int s = G.size() - 2, t = G.size() - 1;
  std::vector<std::vector<llong>> residual(G.size(), std::vector<llong>(G.size(), -1));
  for (int i = 0; i < G.size(); i++) {
    for (int j = 0; j < G.size(); j++) {
      residual[i][j] = G[i][j];
    }
  }
  std::vector<int> parent(G.size());
  while (BFS(residual, s, t, parent)) {
    llong path_flow = INF;
    for (int v = t; v != s; v = parent[v]) {
        int u = parent[v];
        path_flow = std::min(path_flow, residual[u][v]);
    }
    for (int v = t; v != s; v = parent[v]) {
        int u = parent[v];
        residual[u][v] -= path_flow;
        residual[v][u] += path_flow;
    }
  }

  std::vector<bool> visited(G.size(), false);
  DFS(residual, s, visited);
  llong cut = 0;
  for (int i = 0; i < G.size(); i++) {
    for (int j = 0; j < G.size(); j++) {
      if (visited[i] && !visited[j] && G[i][j] > 0) {
        cut += G[i][j];
      }
    }
  }
  return cut;
}

llong solve(std::vector<ladder> &L, const int &N, const int &H) {
  for (int i = 0; i < N; i++) {
    if (L[i].A == 0 && L[i].B == H) {
      return -1;
    }
  }
  std::sort(L.begin(), L.end(), [](const ladder &first, const ladder &second) -> bool {
    return first.X < second.X;
  });

  std::vector<std::vector<llong>> G(N + 2, std::vector<llong>(N + 2, -1));
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (std::max(L[i].A, L[j].A) > std::min(L[i].B, L[j].B)) {
        continue;
      }
      std::vector<std::pair<double, double>> O;
      O.push_back(std::make_pair(std::max(L[i].A, L[j].A), std::min(L[i].B, L[j].B)));
      for (int k = i + 1; k < j; k++) {
        std::vector<std::pair<double, double>> next;
        for (auto &interval : O) {
          if (interval.second <= L[k].A || interval.first >= L[k].B) {
            next.push_back(interval);
          } else if (interval.first < L[k].A && interval.second > L[k].B) {
            next.push_back(std::make_pair(interval.first, L[k].A));
            next.push_back(std::make_pair(L[k].B, interval.second));
          } else if (interval.first < L[k].A && L[k].A <= interval.second) {
            next.push_back(std::make_pair(interval.first, L[k].A));
          } else if (interval.first <= L[k].B && L[k].B < interval.second) {
            next.push_back(std::make_pair(L[k].B, interval.second));
          }
        }
        O = next;
        if (O.empty()) {
          break;
        }
      }
      if (O.empty()) {
        continue;
      }
      llong length = 0;
      for (auto &interval : O) {
        length += (interval.second - interval.first);
      }
      G[i][j] = G[j][i] = length;
    }
  }
  for (int i = 0; i < N; i++) {
    if (L[i].A == 0) {
      G[i][N] = G[N][i] = INF;
    }
    if (L[i].B == H) {
      G[i][N + 1] = G[N + 1][i] = INF;
    }
  }
  return min_cut(G);
}

int main() {
  int T, N, H;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> H;
    std::vector<ladder> L(N);
    for (int i = 0; i < N; i++) {
      std::cin >> L[i].X >> L[i].A >> L[i].B;
    }
    printf("Case #%d: %lld\n", t + 1, solve(L, N, H));
  }
  return 0;
}
