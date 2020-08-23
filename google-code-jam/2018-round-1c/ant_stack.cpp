#include <algorithm>
#include <cassert>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;
typedef std::vector<llong> vllong;

int SIZE = 150;
llong MAX = -1;

int solve(const vllong &W, const int &N) {
  vllong G(SIZE, MAX);
  G[0] = 0;
  for (int i = 0; i < N; i++) {
    for (int j = SIZE - 2; j >= 0; j--) {
      if (G[j] >= 0 && G[j] <= 6 * W[i]) {
        if (G[j + 1] >= 0) {
          G[j + 1] = std::min(G[j + 1], G[j] + W[i]);
        } else {
          G[j + 1] = G[j] + W[i];
        }
      }
    }
  }
  for (int i = SIZE - 1; i >= 0; i--) {
    if (G[i] != MAX) {
      return i;
    }
  }
  return 0;
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N;
    vllong W(N);
    for (int i = 0; i < N; i++) {
      std::cin >> W[i];
    }
    printf("Case #%d: %d\n", t + 1, solve(W, N));
  }
  return 0;
}
