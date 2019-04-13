#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

int accent_suffix(const std::string &A, const std::string &B) {
  for (size_t i = 0; i < std::min(A.size(), B.size()); i++) {
    if (A[A.size() - 1 - i] != B[B.size() - 1 - i]) {
      return i;
    }
  }
  return std::min(A.size(), B.size());
}

int solve(const std::vector<std::string> &W) {
  std::vector<std::vector<int>> S(W.size());
  int out = 0;
  for (std::size_t i = 0; i < W.size(); i++) {
    S[i].resize(W.size());
    for (std::size_t j = 0; j < W.size(); j++) {
      if (i != j) {
        S[i][j] = accent_suffix(W[i], W[j]);
      }
    }
  }
  while (true) {
    int maximum = 0, x = 0, y = 0;
    for (std::size_t i = 0; i < W.size(); i++) {
      for (std::size_t j = 0; j < W.size(); j++) {
        if (maximum < S[i][j]) {
          maximum = S[i][j], x = i, y = j;
        }
      }
    }
    if (maximum == 0) {
      break;
    }
    std::stack<int> V;
    V.push(x), V.push(y);
    while (!V.empty()) {
      int v = V.top();
      V.pop();
      for (std::size_t i = 0; i < W.size(); i++) {
        if (S[i][v] == maximum) {
          S[i][v]--, S[v][i]--, V.push(i);
        }
      }
    }
    for (std::size_t i = 0; i < W.size(); i++) {
      S[i][x] = 0, S[x][i] = 0, S[i][y] = 0, S[y][i] = 0;
    }
    out += 2;
  }
  return out;
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N;
    std::vector<std::string> W(N);
    for (int i = 0; i < N; i++) {
      std::cin >> W[i];
    }
    printf("Case #%d: %d\n", t + 1, solve(W));
  }
  return 0;
}
