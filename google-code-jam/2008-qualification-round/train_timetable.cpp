#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

std::tuple<int, int> solve(
    std::vector<std::pair<int, int>> &QA, std::vector<std::pair<int, int>> &QB,
    const int &N, const int &T) {
  sort(QA.begin(), QA.end());
  sort(QB.begin(), QB.end());
  std::priority_queue<int, std::vector<int>, std::greater<int>> A, B;
  size_t i = 0, j = 0;
  int SA = 0, SB = 0;
  while (i < QA.size() || j < QB.size()) {
    if (j == QB.size() || (i < QA.size() && QA[i].first <= QB[j].first)) {
      if (!A.empty() && A.top() <= QA[i].first) {
        A.pop();
      } else {
        SA++;
      }
      B.push(QA[i].second + T), i++;
    } else {
      if (!B.empty() && B.top() <= QB[j].first) {
        B.pop();
      } else {
        SB++;
      }
      A.push(QB[j].second + T), j++;
    }
  }
  return std::make_tuple(SA, SB);
}

int read_hour() {
  int h, m;
  char c;
  std::cin >> h >> c >> m;
  return h * 60 + m;
}

int main() {
  int N, T, NA, NB, CA, CB;
  std::cin >> N;
  for (int t = 0; t < N; t++) {
    std::cin >> T >> NA >> NB;
    std::vector<std::pair<int, int>> QA, QB;
    for (int i = 0; i < NA; i++) {
      int start = read_hour(), end = read_hour();
      QA.push_back(std::make_pair(start, end));
    }
    for (int i = 0; i < NB; i++) {
      int start = read_hour(), end = read_hour();
      QB.push_back(std::make_pair(start, end));
    }
    std::tie(CA, CB) = solve(QA, QB, N, T);
    printf("Case #%d: %d %d\n", t + 1, CA, CB);
  }
  return 0;
}
