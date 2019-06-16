#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::vector<double> solve(const std::vector<double> &P, const int &N) {
  std::vector<double> out;
  if (N % 2) {
    out.push_back(0.0);
  }
  return out;
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N;
    std::vector<double> P(N + 1);
    for (int i = 0; i <= N; i++) {
      std::cin >> P[i];
    }
    std::vector<double> V = solve(P, N);
    printf("Case #%d: %d\n", t + 1, V.size());
    for (int i = 0; i < V.size(); i++) {
      printf("%.6lf\n", V[i]);
    }
  }
  return 0;
}
