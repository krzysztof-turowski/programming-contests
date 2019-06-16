#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

const int INF = 10000000;

void get_shortest_paths(std::vector<std::vector<int>> &P) {
  int N = P.size();
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (P[i][k] + P[k][j] < P[i][j]) {
          P[i][j] = P[i][k] + P[k][j];
        }
      }
    }
  }
}

int solve(
    std::vector<std::vector<int>> &P, const std::vector<std::pair<int, int>> &X) {
  get_shortest_paths(P);
  for (const auto &x : X) {
    if (P[0][x.first] == INF || P[0][x.second] == INF) {
      return -1;
    }
  }
  int A = P[0][X[0].first], B = P[0][X[0].first], A_town = X[0].first, B_town = X[0].first;
  for (int i = 0; i < X.size() - 1; i++) {
    int A_next =
        std::min(A + P[A_town][X[i].second], B + P[B_town][X[i].second])
            + P[X[i].second][X[i + 1].first];
    int B_next =
        std::min(A + P[A_town][X[i + 1].first], B + P[B_town][X[i + 1].first])
            + P[X[i + 1].first][X[i].second];
    A = A_next, B = B_next, A_town = X[i + 1].first, B_town = X[i].second;
  }
  A += P[A_town][X[X.size() - 1].second], B += P[B_town][X[X.size() - 1].second];
  return std::min(A, B);
}

int main() {
  int T, N, M, K;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> M >> K;
    std::vector<std::vector<int>> G(N, std::vector<int>(N, INF));
    std::vector<std::pair<int, int>> X(K);
    for (int i = 0; i < M; i++) {
      int a, b, g;
      std::cin >> a >> b >> g, --a, --b;
      G[b][a] = G[a][b] = std::min(G[a][b], g);
    }
    for (int i = 0; i < N; i++) {
      G[i][i] = 0;
    }
    for (int i = 0; i < K; i++) {
      std::cin >> X[i].first >> X[i].second, --X[i].first, --X[i].second;
    }
    printf("Case #%d: %d\n", t + 1, solve(G, X));
  }
  return 0;
}
