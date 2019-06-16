#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int count(
    const std::vector<std::pair<int, int>> &Z, const int &x, const int &y,
    const int &w, const int &h) {
  int out = 0;
  for (const auto &s : Z) {
    if (s.first >= x && s.first - x <= w && s.second >= y && s.second - y <= h) {
      out++;
    }
  }
  return out;
}

int solve(const std::vector<std::pair<int, int>> &Z, const int &R) {
  int out = 0;
  for (const auto &s_top : Z) {
    for (const auto &s_left : Z) {
      int S = count(Z, s_left.first, s_top.second, R, R);
      for (const auto &m_top : Z) {
        for (const auto &m_left : Z) {
          int M = count(Z, m_left.first, m_top.second, R, R), MS = 0;
          int width = R - fabs(m_left.first - s_left.first);
          int height = R - fabs(m_top.second - s_top.second);
          int left = std::max(m_left.first, s_left.first);
          int top = std::max(m_top.second, s_top.second);
          if (width >= 0 && height >= 0) {
            MS = count(Z, left, top, width, height);
          }
          out = std::max(out, S + M - MS);
        }
      }
    }
  }
  return out;
}

int main() {
  int T, N, R;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> R;
    std::vector<std::pair<int, int>> Z(N);
    for (int i = 0; i < N; i++) {
      std::cin >> Z[i].first >> Z[i].second;
    }
    printf("Case #%d: %d\n", t + 1, solve(Z, R));
  }
  return 0;
}
