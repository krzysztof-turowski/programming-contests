#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

int DFS(
    const std::vector<std::string> &G, const int &R, const int &C,
    const std::pair<int, int> &P, std::vector<std::vector<bool>> &A) {
  std::queue<std::pair<int, int>> D;
  D.push(P);
  int out = 0;
  std::vector<int> X{-1, 1, 0, 0}, Y{0, 0, -1, 1};
  while (!D.empty()) {
    int x = D.front().first, y = D.front().second;
    D.pop();
    if (x < 0 || x >= R || y < 0 || y >= C || !A[x][y]) {
      continue;
    }
    A[x][y] = false, ++out;
    for (int i = 0; i < X.size(); i++) {
      D.push(std::make_pair(x + X[i], y + Y[i]));
    }
  }
  return out;
}

bool contains(
    const std::vector<std::string> &G, const int &R, const int &C, const std::string &W) {
  if (W[0] == W[1] && W[0] == W[2] && W[0] == W[3]) {
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (G[i][j] == W[0]) {
          return true;
        }
      }
    }
  } else if (W[0] == W[1] && W[2] == W[3]) {
    for (int i = 0; i < R - 1; i++) {
      for (int j = 0; j < C; j++) {
        if (G[i][j] == W[0] && G[i + 1][j] == W[2]) {
          return true;
        }
      }
    }
  } else if (W[0] == W[2] && W[1] == W[3]) {
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C - 1; j++) {
        if (G[i][j] == W[0] && G[i][j + 1] == W[1]) {
          return true;
        }
      }
    }
  } else {
    for (int i = 0; i < R - 1; i++) {
      for (int j = 0; j < C - 1; j++) {
        if (G[i][j] == W[0] && G[i][j + 1] == W[1] && G[i + 1][j] == W[2]
            && G[i + 1][j + 1] == W[3]) {
          return true;
        }
      }
    }
  }
  return false;
}

int find_largest_pattern(
    const std::vector<std::string> &G, const int &R, const int &C, const std::pair<int, int> &Q) {
  int out = 0;
  for (int i = 0; i < 16; i++) {
    std::string W = "BBBB";
    for (int j = 0; j < 4; j++) {
      if ((i >> j) % 2 == 0) {
        W[j] = 'W';
      }
    }
    if (!contains(G, R, C, W)) {
      continue;
    }
    std::vector<std::vector<bool>> A(R, std::vector<bool>(C, false));
    for (int x = 0; x < Q.first; x++) {
      for (int y = 0; y < Q.second; y++) {
        A[x][y] = (G[x][y] == W[0]);
      }
      for (int y = Q.second; y < C; y++) {
        A[x][y] = (G[x][y] == W[1]);
      }
    }
    for (int x = Q.first; x < R; x++) {
      for (int y = 0; y < Q.second; y++) {
        A[x][y] = (G[x][y] == W[2]);
      }
      for (int y = Q.second; y < C; y++) {
        A[x][y] = (G[x][y] == W[3]);
      }
    }
    for (int x = 0; x < R; x++) {
      for (int y = 0; y < C; y++) {
        if (A[x][y]) {
          out = std::max(out, DFS(G, R, C, std::make_pair(x, y), A));
        }
      }
    }
  }
  return out;
}

int solve(const std::vector<std::string> &G, const int &R, const int &C) {
  int best_size = 0;
  for (int x = 0; x < R; x++) {
    for (int y = 0; y < C; y++) {
      best_size = std::max(best_size, find_largest_pattern(G, R, C, std::make_pair(x, y)));
    }
  }
  return best_size;
}

int main() {
  int T, R, C;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> R >> C, std::cin.ignore(256, '\n');
    std::vector<std::string> G(R);
    for (int i = 0; i < R; i++) {
      std::cin >> G[i];
    }
    printf("Case #%d: %d\n", t + 1, solve(G, R, C));
  }
  return 0;
}
