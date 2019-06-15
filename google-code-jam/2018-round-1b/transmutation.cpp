#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

typedef int64_t llong;

int find_negative(const std::vector<llong> &G) {
  for (int i = 0; i < G.size(); i++) {
    if (G[i] < 0) {
      return i;
    }
  }
  return -1;
}

bool is_possible(
    const std::vector<std::vector<llong>> &R, const std::vector<llong> &G, const llong &mid) {
  std::vector<llong> supply(G);
  supply[0] -= mid;
  std::vector<std::vector<llong>> recipes(R.size());
  for (int i = 0; i < R.size(); i++) {
    recipes[i] = R[i];
  }
  while (true) {
    int index = find_negative(supply);
    if (index == -1) {
      return true;
    }
    assert(supply[index] < 0);
    if (recipes[index][index] > 0) {
      return false;
    }
    for (int i = 0; i < supply.size(); i++) {
      if (i == index) {
        continue;
      }
      llong previous = supply[i];
      supply[i] += supply[index] * recipes[index][i];
      // Hack: if debt too large, definitely will not succeed
      if (supply[i] > previous) {
        return false;
      }
    }
    supply[index] = 0;
    for (int i = 0; i < recipes.size(); i++) {
      if (recipes[i][index] > 0) {
        llong k = recipes[i][index];
        for (int j = 0; j < recipes[i].size(); j++) {
          recipes[i][j] += k * recipes[index][j];
        }
        recipes[i][index] = 0;
      }
    }
  }
  return false;
}

llong solve(const std::vector<std::vector<llong>> &R, const std::vector<llong> &G) {
  llong low = 0, high = 1;
  for (const llong &v : G) {
    high += v;
  }
  while (low + 1 < high) {
    llong mid = (low + high) / 2;
    if (is_possible(R, G, mid)) {
      low = mid;
    } else {
      high = mid;
    }
  }
  return low;
}

int main() {
  int T, M, a, b;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> M;
    std::vector<std::vector<llong>> R(M);
    std::vector<llong> G(M);
    for (int i = 0; i < M; i++) {
      R[i].resize(M, 0);
      std::cin >> a >> b;
      R[i][a - 1]++, R[i][b - 1]++;
    }
    for (int i = 0; i < M; i++) {
      std::cin >> G[i];
    }
    printf("Case #%d: %lld\n", t + 1, solve(R, G));
  }
}
