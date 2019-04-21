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

int solve(
    const llong &C, const llong &V, std::priority_queue<llong, std::vector<llong>,
    std::greater<llong>> &M) {
  int out = 0;
  llong N = 0;
  while (N < V) {
    if (!M.empty() && M.top() <= N + 1) {
      N += C * M.top(), M.pop();
    } else {
      N += C * (N + 1), out++;
    }
  }
  return out;
}

int main() {
  int T, D;
  llong C, V, v;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> C >> D >> V;
    std::priority_queue<llong, std::vector<llong>, std::greater<llong>> M;
    for (int i = 0; i < D; i++) {
      std::cin >> v, M.push(v);
    }
    printf("Case #%d: %d\n", t + 1, solve(C, V, M));
  }
  return 0;
}
