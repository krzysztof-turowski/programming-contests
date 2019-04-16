#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

const int MAX = 100;

int find_cover(
    const std::vector<std::pair<double, double>> &P, const double &size, const int &index,
    std::vector<bool> &covered) {
  if (index == MAX) {
    return 0;
  }
  int out = MAX;
  std::vector<double> Y;
  for (size_t i = index; i < P.size(); i++) {
    if (covered[i]) {
      continue;
    }
    if (fabs(P[index].first - P[i].first) <= size && fabs(P[index].second - P[i].second) <= size) {
      Y.push_back(P[i].second);
    }
  }
  auto last = std::unique(Y.begin(), Y.end());
  Y.erase(last, Y.end());
  for (const auto &y : Y) {
    std::vector<bool> new_covered(covered);
    size_t new_index = MAX;
    for (size_t i = index; i < P.size(); i++) {
      if (P[i].first - P[index].first <= size && P[i].second >= y && P[i].second - y <= size) {
        new_covered[i] = true;
      }
      if (!new_covered[i]) {
        new_index = std::min(new_index, i);
      }
    }
    out = std::min(out, find_cover(P, size, new_index, new_covered) + 1);
  }
  return out;
}

int solve(const std::vector<std::pair<double, double>> &P, const int &k) {
  double x_max = 0, y_max = 0;
  for (size_t i = 0; i < P.size(); i++) {
    x_max = std::max(x_max, P[i].first), y_max = std::max(y_max, P[i].second);
  }
  double size_low = 0, size_high = std::max(x_max, y_max);
  while (size_high - size_low >= 0.5) {
    double size_mid = (size_low + size_high) / 2;
    std::vector<bool> covered(P.size(), false);
    int count = find_cover(P, size_mid, 0, covered);
    if (count > k) {
      size_low = size_mid;
    } else {
      size_high = size_mid;
    }
  }
  return static_cast<int>(size_high);
}

int main() {
  int T, n, k;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> n >> k;
    std::vector<std::pair<double, double>> P(n);
    for (int i = 0; i < n; i++) {
      std::cin >> P[i].first >> P[i].second;
    }
    std::sort(P.begin(), P.end());
    printf("Case #%d: %d\n", t + 1, solve(P, k));
  }
  return 0;
}
