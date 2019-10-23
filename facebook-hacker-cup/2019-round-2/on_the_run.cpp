#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

bool solve(
    const int &N, const int &M, const std::pair<int, int> &X,
    const std::vector<std::pair<int, int>> &A) {
  if (N == 1 || M == 1) {
    return true;
  }
  if (A.size() == 1) {
    return false;
  }
  if ((A[0].first + A[0].second) % 2 != (A[1].first + A[1].second) % 2) {
    return false;
  }
  if ((A[0].first + A[0].second) % 2 != (X.first + X.second) % 2) {
    return false;
  }
  return true;
}

int main() {
  int T, N, M, K;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::pair<int, int> X;
    std::cin >> N >> M >> K >> X.first >> X.second;
    std::vector<std::pair<int, int>> A(K);
    for (int i = 0; i < K; i++) {
      std::cin >> A[i].first >> A[i].second;
    }
    printf("Case #%d: %c\n", t + 1, solve(N, M, X, A) ? 'Y' : 'N');
  }
  return 0;
}
