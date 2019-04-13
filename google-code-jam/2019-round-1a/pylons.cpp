#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::tuple<std::string, std::vector<std::pair<int, int>>> solve(const int &R, const int &C) {
  std::vector<std::pair<int, int>> V;
  if ((R == 1) || (R == 2 && C <= 4) || (R == 3 && C == 3)) {
    return std::make_tuple("IMPOSSIBLE", V);
  }
  if (R == 2) {
    for (int i = 0; i < C; i++) {
      V.push_back(std::make_pair(1, i % C + 1));
      V.push_back(std::make_pair(2, (i + 3) % C + 1));
    }
    return std::make_tuple("POSSIBLE", V);
  }
  if (R == 3) {
    for (int i = 0; i < C; i++) {
      V.push_back(std::make_pair(1, (i + 2) % C + 1));
      V.push_back(std::make_pair(2, i % C + 1));
      V.push_back(std::make_pair(3, (i + 2) % C + 1));
    }
    return std::make_tuple("POSSIBLE", V);
  }
  if (R == 4 && C == 4) {
    for (int i = 0; i < C - 1; i++) {
      for (int j = 0; j < R; j++) {
        V.push_back(std::make_pair(j + 1, (j % 2 ? (i + 2) % C : i % C) + 1));
      }
    }
    V.push_back(std::make_pair(3, 4));
    V.push_back(std::make_pair(4, 2));
    V.push_back(std::make_pair(1, 4));
    V.push_back(std::make_pair(2, 2));
    return std::make_tuple("POSSIBLE", V);
  }
  for (int j = 0; j < (R - 2) / 2; j++) {
    for (int i = 0; i < C; i++) {
      V.push_back(std::make_pair(2 * j + 1, i % C + 1));
      V.push_back(std::make_pair(2 * j + 2, (i + C - 2) % C + 1));
    }
  }
  if (R % 2) {
    for (int i = 0; i < C; i++) {
      V.push_back(std::make_pair(R - 2, i % C + 1));
      V.push_back(std::make_pair(R - 1, (i + 2) % C + 1));
      V.push_back(std::make_pair(R, i % C + 1));
    }
  } else {
    for (int i = 0; i < C; i++) {
      V.push_back(std::make_pair(R - 1, i % C + 1));
      V.push_back(std::make_pair(R, (i + C - 2) % C + 1));
    }
  }
  return std::make_tuple("POSSIBLE", V);
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int R, C;
    std::string S;
    std::vector<std::pair<int, int>> V;
    std::cin >> R >> C;
    std::tie(S, V) = solve(std::min(R, C), std::max(R, C));
    printf("Case #%d: %s\n", t + 1, S.c_str());
    for (const auto &v : V) {
      if (R <= C) {
        printf("%d %d\n", v.first, v.second);
      } else {
        printf("%d %d\n", v.second, v.first);
      }
    }
    if (!V.empty()) {
      for (size_t i = 0; i < V.size() - 1; i++) {
        int dr = V[i].first - V[i + 1].first, dc = V[i].second - V[i + 1].second;
        assert(dr != 0), assert(dc != 0), assert(dr != dc), assert(dr != -dc);
      }
    }
  }
  return 0;
}
