#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::string solve(std::string &S, const int &K) {
  int out = 0;
  for (int i = 0; i <= S.size() - K; i++) {
    if (S[i] == '-') {
      for (int j = i; j < i + K; j++) {
        S[j] = S[j] == '+' ? '-' : '+';
      }
      out++;
    }
  }
  for (int i = S.size() - K + 1; i < S.size(); i++) {
    if (S[i] == '-') {
      return "IMPOSSIBLE";
    }
  }
  return std::to_string(out);
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int K;
    std::string S;
    std::cin >> S >> K;
    printf("Case #%d: %s\n", t + 1, solve(S, K).c_str());
  }
  return 0;
}
