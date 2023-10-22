#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using llong = int64_t;
using ldouble = long double;

bool both_ways(const std::pair<llong, llong> &A, const std::pair<llong, llong> &B) {
  if (A.first >= B.first && A.second >= B.second) {
    return false;
  }
  if (A.first <= B.first && A.second <= B.second) {
    return false;
  }
  return true;
}

std::pair<llong, llong> get_transition(
    const std::pair<llong, llong> &A, const std::pair<llong, llong> &B) {
  return std::make_pair(A.first - B.first, B.second - A.second);
}

bool are_equal(
    const std::pair<llong, llong> &A, const std::pair<llong, llong> &B) {
  return A.first * B.second == B.first * A.second;
}

ldouble get_value(const std::pair<llong, llong> &v) {
  return static_cast<ldouble>(v.first) / v.second;
}

int solve(const std::vector<std::pair<llong, llong>> &M) {
  std::vector<std::pair<llong, llong>> transition;
  for (int i = 0; i < M.size(); i++) {
    for (int j = i + 1; j < M.size(); j++) {
      if (both_ways(M[i], M[j])) {
        transition.push_back(get_transition(M[i], M[j]));
      }
    }
  }
  std::sort(
      transition.begin(), transition.end(),
      [](const std::pair<llong, llong> &a, const std::pair<llong, llong> &b) {
          return get_value(a) < get_value(b);
      });
  int out = 1;
  for (int i = 0; i < transition.size(); i++) {
    if (i > 0 && are_equal(transition[i], transition[i - 1])) {
      continue;
    }
    out++;
  }
  return out;
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N;
    std::vector<std::pair<llong, llong>> M(N);
    for (int i = 0; i < N; i++) {
      std::cin >> M[i].first >> M[i].second;
    }
    printf("Case #%d: %d\n", t + 1, solve(M));
  }
  return 0;
}
