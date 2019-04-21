#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

bool match_vertex(
    const std::vector<std::vector<int>> &A, const int &N, const int &color, const int &u,
    std::vector<int> &left, std::vector<int> &right, std::vector<bool> &visited) {
  visited[u] = true;
  for (int v = 0; v < N; v++) {
    if (A[u][v] != color) {
      continue;
    }
    if (right[v] == -1) {
      left[u] = v, right[v] = u;
      return true;
    }
  }
  for (int v = 0; v < N; v++) {
    if (A[u][v] != color) {
      continue;
    }
    if (!visited[right[v]] && match_vertex(A, N, color, right[v], left, right, visited)) {
      left[u] = v, right[v] = u;
      return true;
    }
  }
  return false;
}

int get_matching_size(const std::vector<std::vector<int>> &A, const int &N, const int &color) {
  std::vector<int> left(N, -1), right(N, -1);
  int total = 0;
  while (true) {
    std::vector<bool> visited(N, false);
    int count = 0;
    for (int v = 0; v < N; v++) {
      if (left[v] == -1 && match_vertex(A, N, color, v, left, right, visited)) {
        count++;
      }
    }
    if (count == 0) {
      return total;
    }
    total += count;
  }
  return 0;
}

int solve(const std::vector<std::vector<int>> &A, const int &N) {
  int out = N * N;
  for (int color = -N; color <= N; color++) {
    out -= get_matching_size(A, N, color);
  }
  return out;
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N;
    std::vector<std::vector<int>> A(N);
    for (int i = 0; i < N; i++) {
      A[i].resize(N);
      for (int j = 0; j < N; j++) {
        std::cin >> A[i][j];
      }
    }
    printf("Case #%d: %d\n", t + 1, solve(A, N));
  }
  return 0;
}
