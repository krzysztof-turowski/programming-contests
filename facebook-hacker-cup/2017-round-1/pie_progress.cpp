#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using llong = int64_t;

const llong INF = (1LL << 62);

llong solve(const std::vector<std::vector<int>> &S, const int &N, const int &M) {
  std::vector<llong> values(N + 1, INF);
  values[0] = 0;
  for (int i = 0; i < N; i++) {
    std::vector<llong> next(N + 1, INF);
    for (int j = i; j <= N; j++) {
      llong current = 0;
      for (int k = 0; k <= M; k++) {
        if (j + k > N) {
          break;
        }
        next[j + k] = std::min(next[j + k], values[j] + current + k * k);
        if (k < M) {
          current += S[i][k];
        }
      }
    }
    values = next;
  }
  return values[N];
}

int main() {
  int T, N, M;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> M;
    std::vector<std::vector<int>> S(N, std::vector<int>(M));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        std::cin >> S[i][j];
      }
      std::sort(S[i].begin(), S[i].end());
    }
    printf("Case #%d: %lld\n", t + 1, solve(S, N, M));
  }
  return 0;
}
