#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::string solve(std::vector<std::string> &S, const int &left, const int &right) {
  std::string out(1, 'z' + 1);
  if (left == right) {
    std::stringstream text;
    for (const auto &s : S) {
      text << s;
    }
    std::string word = text.str();
    if (word < out) {
      out = word;
    }
  } else {
    for (int i = left; i <= right; i++) {
      swap(S[left], S[i]);
      std::string word = solve(S, left + 1, right);
      if (word < out) {
        out = word;
      }
      swap(S[left], S[i]);
    }
  }
  return out;
}

int main() {
  int T, M;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> M;
    std::vector<std::string> S(M);
    for (int i = 0; i < M; i++) {
      std::cin >> S[i];
    }
    printf("Case #%d: %s\n", t + 1, solve(S, 0, M - 1).c_str());
  }
  return 0;
}
