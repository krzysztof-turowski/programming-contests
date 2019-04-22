#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

std::pair<llong, llong> solve(const llong &N, const llong &K) {
  std::priority_queue<std::pair<llong, llong>> Q;
  Q.push(std::make_pair(N, 1));
  llong out = 0;
  while (true) {
    auto best = Q.top();
    Q.pop();
    while (!Q.empty() && best.first == Q.top().first) {
      best.second += Q.top().second, Q.pop();
    }
    if (best.first % 2) {
      Q.push(std::make_pair(best.first / 2, best.second * 2));
    } else {
      Q.push(std::make_pair((best.first - 1) / 2, best.second));
      Q.push(std::make_pair(best.first / 2, best.second));
    }
    out += best.second;
    if (out >= K) {
      return std::make_pair((best.first - 1) / 2, best.first / 2);
    }
  }
  return std::make_pair(-1L, -1L);
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    llong N, K;
    std::cin >> N >> K;
    std::pair<llong, llong> P = solve(N, K);
    printf("Case #%d: %lld %lld\n", t + 1, P.second, P.first);
  }
  return 0;
}
