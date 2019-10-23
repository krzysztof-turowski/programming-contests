#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>

std::string solve(std::vector<std::string> &B, const int &R, const int &C) {
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (B[i][j] != '?') {
        for (int k = j - 1; k >= 0 && B[i][k] == '?'; k--) {
          B[i][k] = B[i][j];
        }
        for (int k = j + 1; k < C && B[i][k] == '?'; k++) {
          B[i][k] = B[i][j];
        }
      }
    }
  }
  for (int i = 0; i < R; i++) {
    if (B[i][0] != '?') {
      for (int k = i - 1; k >= 0 && B[k][0] == '?'; k--) {
        B[k] = B[i];
      }
      for (int k = i + 1; k < R && B[k][0] == '?'; k++) {
        B[k] = B[i];
      }
    }
  }
  std::stringstream out;
  for (const auto &s : B) {
    out << s << '\n';
  }
  return out.str();
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
    printf("Case #%d:\n%s", t + 1, solve(B, R, C).c_str());
  }
  return 0;
}
