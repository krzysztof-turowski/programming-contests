#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;
typedef std::pair<llong, llong> fraction;

const llong INF = 1e9L + 1;

bool heavier(const fraction &A, const fraction &B) {
  return A.first >= B.first && A.second >= B.second;
}

fraction get_transition(
    const fraction &A, const fraction &B) {
  llong num = A.first - B.first, den = B.second - A.second;
  return std::make_pair(num > 0 ? num : -num, den > 0 ? den : -den);
}

bool are_less(const fraction &A, const fraction &B) {
  return A.first * B.second < B.first * A.second;
}

fraction farey_find(const fraction &low, const fraction &high) {
  fraction left = std::make_pair(0, 1), right = std::make_pair(1, 1);
  while (true) {
    auto mid = std::make_pair(left.first + right.first, left.second + right.second);
    if (!are_less(low, mid)) {
      left = mid;
    } else if (!are_less(mid, high)) {
      right = mid;
    } else {
      return mid;
    }
  }
  return std::make_pair(0, 0);
}

std::string solve(const std::vector<fraction> &M) {
  std::vector<fraction> transition;
  fraction low = std::make_pair(1, INF), high = std::make_pair(INF, 1);
  for (int i = 0; i < M.size(); i++) {
    for (int j = i + 1; j < M.size(); j++) {
      if (heavier(M[i], M[j])) {
        return "IMPOSSIBLE";
      }
      if (heavier(M[j], M[i])) {
        continue;
      }
      auto next = get_transition(M[i], M[j]);
      if (M[i].second < M[j].second) {
        if (are_less(low, next)) {
          low = next;
        }
      } else {
        if (are_less(next, high)) {
          high = next;
        }
      }
    }
  }
  if (!are_less(low, high)) {
    return "IMPOSSIBLE";
  }
  if (low.first / low.second < high.first / high.second && high.first % high.second != 0) {
    return std::to_string(1) + " " + std::to_string(low.first / low.second + 1);
  }
  if (low.first / low.second + 1 < high.first / high.second) {
    return std::to_string(1) + " " + std::to_string(low.first / low.second + 1);
  }
  llong shift = low.first / low.second;
  low.first -= shift * low.second, high.first -= shift * high.second;
  auto out = farey_find(low, high);
  out.first += shift * out.second;
  return std::to_string(out.second) + " " + std::to_string(out.first);
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N;
    std::vector<fraction> M(N);
    for (int i = 0; i < N; i++) {
      std::cin >> M[i].first >> M[i].second;
    }
    printf("Case #%d: %s\n", t + 1, solve(M).c_str());
  }
  return 0;
}
