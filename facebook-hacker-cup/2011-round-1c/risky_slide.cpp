#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int get_slide(const std::string &S) {
  int out = 0, start = 0;
  for (int i = 0; i < S.size(); i++) {
    start += S[i] - '0';
    for (int j = i + 1; j < S.size(); j++) {
      int energy = start, tiles = 0;
      for (int k = j; energy > 0 && k < S.size(); k++) {
        energy -= (S[k] - '0');
        if (energy >= 0) {
          tiles++;
        }
      }
      out = std::max(out, tiles);
    }
  }
  return out;
}

int solve(std::vector<std::string> &B) {
  int out = 0;
  for (int i = 0; i < B.size(); i++) {
    out = std::max(out, get_slide(B[i]));
    std::reverse(B[i].begin(), B[i].end());
    out = std::max(out, get_slide(B[i]));
  }
  for (int i = 0; i < B[0].size(); i++) {
    std::stringstream S;
    for (int j = 0; j < B.size(); j++) {
      S << B[j][i];
    }
    std::string A = S.str();
    out = std::max(out, get_slide(A));
    std::reverse(A.begin(), A.end());
    out = std::max(out, get_slide(A));
  }
  return out;
}

int main() {
  int T, R, C;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> R >> C, std::cin.ignore(256, '\n');
    std::vector<std::string> B(R);
    for (int i = 0; i < R; i++) {
      std::cin >> B[i];
    }
    printf("Case #%d: %d\n", t + 1, solve(B));
  }
  return 0;
}
