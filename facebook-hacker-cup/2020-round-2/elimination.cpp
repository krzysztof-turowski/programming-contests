#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

const int MAX = 8000;
std::vector<std::vector<double>> lose_B, lose_W;

void precompute(int N) {
  lose_B = std::vector(N, std::vector(N, 0.0));
  lose_W = std::vector(N, std::vector(N, 0.0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i == 0 && j == 0) {
        continue;
      }
      int denominator = (i + j + 1) * (i + j);
      lose_B[i][j] =  static_cast<double>(i * (i - 1)) / denominator;
      lose_W[i][j] = static_cast<double>(
          j * (j - 1) + 2 * j * (i + 1)) / ((i + j + 1) * (i + j));
    }
  }
}

std::vector<double> solve(int N, double P) {
  std::vector<std::vector<double>> E(N, std::vector(N, 0.0));
  for (int i = 1; i < N; i++) {
    E[i][0] = (1 + P * E[i - 1][0] * lose_B[i][0]
        + (1 - P) * E[i - 1][0] * lose_W[0][i]);
    E[0][i] = (1 + P * E[0][i - 1] * lose_W[0][i]
        + (1 - P) * E[0][i - 1] * lose_B[i][0]);
  }
  for (int i = 1; i < N; i++) {
    for (int j = 1; j < N; j++) {
      E[i][j] += P * (
          E[i - 1][j] * lose_B[i][j] + E[i][j - 1] * lose_W[i][j]);
      E[i][j] += (1 - P) * (
          E[i - 1][j] * lose_W[j][i] + E[i][j - 1] * lose_B[j][i]);
      E[i][j] += 1;
    }
  }
  std::vector<double> out;
  for (int i = 0; i < N; i++) {
    out.push_back(E[N - i - 1][i]);
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  precompute(MAX);
  for (int t = 0; t < T; t++) {
    int N;
    double P;
    std::cin >> N >> P;
    auto out = solve(N, P);
    printf("Case #%d:\n", t + 1);
    for (int i = 0; i < N; i++) {
      printf("%.8f\n", out[i]);
    }
  }
  return 0;
}
