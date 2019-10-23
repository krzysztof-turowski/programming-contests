#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> generate_board(const int &R, const int &C) {
  std::stringstream S;
  for (int i = 0; i < C - 2; i++) {
    S << "x.";
  }
  std::string odd = S.str() + "x", even = odd + ".x";
  std::vector<std::string> out(R);
  for (int i = 0; i < R; i++) {
    out[i] = i % 2 ? odd : even;
  }
  return out;
}

std::pair<int, double> solve(const std::vector<std::string> &S, const int &K) {
  std::pair<int, double> out(0, 0);
  for (int i = 1; i < S[0].size(); i += 2) {
    std::vector<double> P(S[0].size(), 0.0);
    P[i] = 1;
    for (int j = 1; j < S.size(); j++) {
      std::vector<double> P_next(S[j].size(), 0.0);
      if (j % 2) {
        for (int k = 0; k < S[j].size(); k++) {
          if (S[j][k] == '.') {
            P_next[k] += P[k + 1];
          } else if (k == 0) {
            P_next[k + 1] += P[k + 1];
          } else if (k == S[j].size() - 1) {
            P_next[k - 1] += P[k + 1];
          } else {
            P_next[k - 1] += 0.5 * P[k + 1];
            P_next[k + 1] += 0.5 * P[k + 1];
          }
        }
      } else {
        for (int k = 1; k < S[j].size() - 1; k++) {
          if (S[j][k] == '.') {
            P_next[k] += P[k - 1];
          } else if (k == 0) {
            P_next[k + 1] += P[k - 1];
          } else if (k == S[j].size() - 1) {
            P_next[k - 1] += P[k - 1];
          } else {
            P_next[k - 1] += 0.5 * P[k - 1];
            P_next[k + 1] += 0.5 * P[k - 1];
          }
        }
      }
      P = P_next;
    }
    if (out.second < P[2 * K + 1]) {
      out.first = i / 2, out.second = P[2 * K + 1];
    }
  }
  return out;
}

int main() {
  int T, R, C, K, M;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> R >> C >> K >> M;
    std::vector<std::string> S = generate_board(R, C);
    for (int i = 0; i < M; i++) {
      int r, c;
      std::cin >> r >> c;
      S[r][2 * c] = '.';
    }
    auto G = solve(S, K);
    printf("Case #%d: %d %.6lf\n", t + 1, G.first, G.second);
  }
  return 0;
}
