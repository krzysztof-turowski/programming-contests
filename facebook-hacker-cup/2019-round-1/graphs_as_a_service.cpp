#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef int64_t llong;

std::string solve(const std::vector<std::vector<llong>> &G) {
  int N = G.size();
  std::vector<std::vector<llong>> H(N, std::vector<llong>(N, -1));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      H[i][j] = G[i][j];
    }
  }
  for (int k = 0; k < N; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (H[i][k] >= 0 && H[k][j] >= 0) {
          if (H[i][j] == -1 || H[i][k] + H[k][j] < H[i][j]) {
            H[i][j] = H[i][k] + H[k][j];
          }
        }
      }
    }
  }
  int M = 0;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (G[i][j] > 0 && H[i][j] != G[i][j]) {
        return "Impossible\n";
      }
      if (G[i][j] > 0) {
        M++;
      }
    }
  }
  std::stringstream S;
  S << M << std::endl;
  for (int i = 0; i < N; i++) {
    for (int j = i + 1; j < N; j++) {
      if (G[i][j] > 0) {
        S << i + 1 << " " << j + 1 << " " << G[i][j] << std::endl;
      }
    }
  }
  return S.str();
}

int main() {
  int T, N, M;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> M;
    std::vector<std::vector<llong>> G(N, std::vector<llong>(N, -1));
    int X, Y, Z;
    bool consistent = true;
    for (int i = 0; i < M; i++) {
      std::cin >> X >> Y >> Z;
      if (G[X - 1][Y - 1] != -1 && G[X - 1][Y - 1] != Z) {
        consistent = false;
      } else {
        G[X - 1][Y - 1] = G[Y - 1][X - 1] = Z;
      }
    }
    for (int i = 0; i < N; i++) {
      G[i][i] = 0;
    }
    printf("Case #%d: %s", t + 1, consistent ? solve(G).c_str() : "Impossible\n");
  }
}
