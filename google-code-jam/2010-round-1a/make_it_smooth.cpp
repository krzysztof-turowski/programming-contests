#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

const int MAX = 256;
const int INF = 1000000000;

int solve(std::vector<int> &A, int &D, int &I, int &M, int &N) {
  std::vector<int> previous(MAX, 0);
  for (int k = 0; k < N; k++) {
    std::vector<int> cost(MAX, INF);
    for (int i = 0; i < MAX; i++) {
        cost[i] = std::min(
          previous[i] + D, static_cast<int>(fabs(A[k] - i)) + k * D);
    }
    if (M > 0) {
      for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
          int difference = fabs(A[k] - i) + I * std::max(
            0, static_cast<int>(fabs(i - j) - 1) / M);
          cost[i] = std::min(cost[i], previous[j] + difference);
        }
      }
    } else {
      for (int i = 0; i < MAX; i++) {
        cost[i] = std::min(
          cost[i], previous[i] + static_cast<int>(fabs(A[k] - i)));
      }
    }
    std::swap(previous, cost);
  }
  int out = D * N;
  for (int i = 0; i < MAX; i++) {
    out = std::min(out, previous[i]);
  }
  return out;
}

int main() {
  int T, D, I, M, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> D >> I >> M >> N;
    std::vector<int> A(N, 0);
    for (int i = 0; i < N; i++) {
      std::cin >> A[i];
    }
    printf("Case #%d: %d\n", t + 1, solve(A, D, I, M, N));
  }
  return 0;
}
