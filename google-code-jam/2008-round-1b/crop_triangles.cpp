#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

std::vector<std::pair<llong, llong>> generate_input(
    const int &N, const llong &A, const llong &B, const llong &C, const llong &D,
    std::pair<llong, llong> &P, const llong &M) {
  std::vector<std::pair<llong, llong>> out;
  for (int i = 0; i < N; i++) {
    out.push_back(P);
    P.first = (A * P.first + B) % M, P.second = (C * P.second + D) % M;
  }
  return out;
}

llong solve(const std::vector<std::pair<llong, llong>> &P) {
  std::vector<std::vector<llong>> S(3, {0, 0, 0});
  for (const auto &p : P) {
    S[p.first % 3][p.second % 3]++;
  }
  llong out = 0;
  // All identical
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      out += S[i][j] * (S[i][j] - 1) * (S[i][j] - 2) / 6;
    }
  }
  // First (0, 1, 2)
  for (int i = 0; i < 3; i++) {
    out += S[0][i] * S[1][i] * S[2][i];
  }
  // Second (0, 1, 2)
  for (int i = 0; i < 3; i++) {
    out += S[i][0] * S[i][1] * S[i][2];
  }
  // Both (0, 1, 2)
  out += S[0][0] * S[1][1] * S[2][2] + S[0][0] * S[1][2] * S[2][1];
  out += S[0][1] * S[1][0] * S[2][2] + S[0][1] * S[1][2] * S[2][0];
  out += S[0][2] * S[1][0] * S[2][1] + S[0][2] * S[1][1] * S[2][0];
  return out;
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    llong A, B, C, D, X0, Y0, M;
    std::cin >> N >> A >> B >> C >> D >> X0 >> Y0 >> M;
    auto P = std::make_pair(X0, Y0);
    printf("Case #%d: %lld\n", t + 1, solve(generate_input(N, A, B, C, D, P, M)));
  }
  return 0;
}
