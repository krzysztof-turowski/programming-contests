#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <string>
#include <vector>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int get_longest_path(
    const int &v, std::vector<std::set<int>> &G, const std::vector<int> &B) {
  int out = 1;
  for (const auto &u : G[v]) {
    if (u == B[v]) {
      continue;
    }
    out = std::max(out, 1 + get_longest_path(u, G, B));
  }
  return out;
}

int solve(const std::vector<int> &B, const int &N) {
  int first = 0;
  REP(i, N) {
    std::vector<bool> visited(N, false);
    int v = B[i];
    int count = 1;
    while (true) {
      if (v == i) {
        first = std::max(first, count);
        break;
      }
      if (visited[v]) {
        break;
      }
      count++, visited[v] = true, v = B[v];
    }
  }

  int second = 0;
  std::vector<std::set<int>> reverse(N);
  REP(i, N) {
    reverse[B[i]].insert(i);
  }
  REP(i, N) {
    if (i < B[i] && B[B[i]] == i) {
      second += get_longest_path(i, reverse, B) + get_longest_path(B[i], reverse, B);
    }
  }
  return std::max(first, second);
}

int main() {
  int T, N, v;
  std::cin >> T;
  REP(t, T) {
    std::cin >> N;
    std::vector<int> B(N);
    REP(i, N) {
      std::cin >> v, B[i] = v - 1;
    }
    printf("Case #%d: %d\n", t + 1, solve(B, N));
  }

  return 0;
}
