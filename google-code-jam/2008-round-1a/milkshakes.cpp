#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::string solve(
    const std::vector<int> &malted, std::vector<std::set<int>> &unmalted,
    const int &N) {
  std::vector<bool> out(N, false);
  int count = 0;
  while (true) {
    std::set<int> unsatisfied;
    for (size_t i = 0; i < unmalted.size(); i++) {
      if (malted[i] == -1 && unmalted[i].empty()) {
        return "IMPOSSIBLE";
      }
      if (!out[malted[i]] && unmalted[i].empty()) {
        out[malted[i]] = true, unsatisfied.insert(malted[i]);
      }
    }
    if (unsatisfied.empty()) {
      break;
    }
    for (const int &i : unsatisfied) {
      for (size_t j = 0; j < unmalted.size(); j++) {
        unmalted[j].erase(i);
      }
    }
  }
  std::string S(2 * N - 1, ' ');
  for (int i = 0; i < N; i++) {
    S[2 * i] = out[i] ? '1' : '0';
  }
  return S;
}

int main() {
  int C, N, M;
  std::cin >> C;
  for (int c = 0; c < C; c++) {
    std::cin >> N >> M;
    std::vector<int> malted(M, -1);
    std::vector<std::set<int>> unmalted(M);
    int T, X, Y;
    for (int i = 0; i < M; i++) {
      std::cin >> T;
      for (int j = 0; j < T; j++) {
        std::cin >> X >> Y;
        if (Y == 1) {
          malted[i] = X - 1;
        } else {
          unmalted[i].insert(X - 1);
        }
      }
    }
    printf("Case #%d: %s\n", c + 1, solve(malted, unmalted, N).c_str());
  }
  return 0;
}
