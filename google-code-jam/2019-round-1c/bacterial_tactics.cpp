#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define LEFT 0
#define RIGHT 1
#define DOWN 2
#define UP 3

int minimum_exclusion(const std::set<int> &S) {
  for (int i = 0; i <= S.size(); i++) {
    if (S.find(i) == S.end()) {
      return i;
    }
  }
  return 0;
}

std::pair<int, int> grundy(
    const int &L, const int &R, const int &D, const int &U,
    std::vector<std::map<std::pair<int, int>, int>> &P,
    std::map<std::tuple<int, int, int, int>, int> &lookup) {
  if (L == R || D == U) {
    return std::make_pair(0, 0);
  }
  int result = 0;
  if (lookup.find(std::make_tuple(L, R, D, U)) == lookup.end()) {
    std::set<int> S;
    for (int i = L; i < R; i++) {
      auto index = std::make_pair(i, D);
      if (D <= P[LEFT][index] || P[RIGHT][index] < U) {
        continue;
      }
      int left = grundy(L, i, D, U, P, lookup).second;
      int right = grundy(i + 1, R, D, U, P, lookup).second;
      int opponent_wins = left ^ right;
      S.insert(opponent_wins);
      if (!opponent_wins) {
        result += U - D;
      }
    }
    for (int i = D; i < U; i++) {
      auto index = std::make_pair(L, i);
      if (L <= P[DOWN][index] || P[UP][index] < R) {
        continue;
      }
      int left = grundy(L, R, D, i, P, lookup).second;
      int right = grundy(L, R, i + 1, U, P, lookup).second;
      int opponent_wins = left ^ right;
      S.insert(opponent_wins);
      if (!opponent_wins) {
        result += R - L;
      }
    }
    lookup[std::make_tuple(L, R, D, U)] = minimum_exclusion(S);
  }
  return std::make_pair(result, lookup[std::make_tuple(L, R, D, U)]);
}

int solve(const int &R, const int &C, std::vector<std::string> &M) {
  std::vector<std::map<std::pair<int, int>, int>> P;
  P.resize(4);
  for (int i = 0; i < R; i++) {
    int left = -1, right = C;
    for (int j = 0; j < C; j++) {
      if (M[i][j] == '#') {
        left = j;
      }
      P[LEFT][std::make_pair(i, j)] = left;
    }
    for (int j = C - 1; j >= 0; j--) {
      if (M[i][j] == '#') {
        right = j;
      }
      P[RIGHT][std::make_pair(i, j)] = right;
    }
  }
  for (int i = 0; i < C; i++) {
    int up = R, down = -1;
    for (int j = 0; j < R; j++) {
      if (M[j][i] == '#') {
        down = j;
      }
      P[DOWN][std::make_pair(j, i)] = down;
    }
    for (int j = R - 1; j >= 0; j--) {
      if (M[j][i] == '#') {
        up = j;
      }
      P[UP][std::make_pair(j, i)] = up;
    }
  }
  std::map<std::tuple<int, int, int, int>, int> lookup;
  auto out = grundy(0, R, 0, C, P, lookup);
  return out.second ? out.first : 0;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int R, C;
    std::cin >> R >> C;
    std::cin.ignore(256, '\n');
    std::vector<std::string> M(R);
    for (int i = 0; i < R; i++) {
        std::cin >> M[i];
    }
    printf("Case #%d: %d\n", t + 1, solve(R, C, M));
  }
  return 0;
}
