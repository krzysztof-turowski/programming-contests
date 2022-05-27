#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define INF 1000000000

std::map<std::pair<int, int>, std::vector<int>> c;
std::map<std::pair<int, int>, int> v, m;

std::vector<int> C(int L, int R, const std::vector<std::vector<int>> &S) {
  if (L == R) {
    return S[L];
  }
  if (!c.count(std::make_pair(L, R))) {
    int mid = (L + R) / 2;
    std::vector<int> left = C(L, mid, S), right = C(mid + 1, R, S), low;
    for (int i = 0; i < left.size(); i++) {
      low.push_back(std::min(left[i], right[i]));
    }
    c[std::make_pair(L, R)] = low;
  }
  return c[std::make_pair(L, R)];
}

int V(int L, int R, const std::vector<std::vector<int>> &S) {
  if (!v.count(std::make_pair(L, R))) {
    int sum = 0;
    for (const auto &s : C(L, R, S)) {
      sum += s;
    }
    v[std::make_pair(L, R)] = sum;
  }
  return v[std::make_pair(L, R)];
}

int M(int L, int R, const std::vector<std::vector<int>> &S) {
  if (L == R) {
    return 0;
  }
  if (!m.count(std::make_pair(L, R))) {
    int best = INF;
    for (int i = L; i < R; i++) {
      best = std::min(best,
          M(L, i, S) + M(i + 1, R, S) + 2 * V(L, i, S) + 2 * V(i + 1, R, S));
    }
    m[std::make_pair(L, R)] = best - 4 * V(L, R, S);
  }
  return m[std::make_pair(L, R)];
}

int solve(const std::vector<std::vector<int>> &S, int E) {
  int out = M(0, E - 1, S);
  m.clear(), v.clear(), c.clear();
  return out;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int E, W;
    std::cin >> E >> W;
    std::vector<std::vector<int>> S(E + 2, std::vector<int>(W));
    for (int i = 1; i <= E; i++) {
      for (int j = 0; j < W; j++) {
        std::cin >> S[i][j];
      }
    }
    printf("Case #%d: %d\n", t + 1, solve(S, E + 2));
  }
  return 0;
}
