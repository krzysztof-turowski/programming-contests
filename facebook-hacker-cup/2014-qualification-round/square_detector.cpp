#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

auto find_start(const std::vector<std::string> &S, const int &N) {
  REP(i, N) {
    REP(j, N) {
      if (S[i][j] == '#') {
        return std::make_pair(i, j);
      }
    }
  }
  return std::make_pair(-1, -1);
}

auto find_end(const std::vector<std::string> &S, const int &N) {
  FORD(i, N - 1, 0) {
    FORD(j, N - 1, 0) {
      if (S[i][j] == '#') {
        return std::make_pair(i, j);
      }
    }
  }
  return std::make_pair(-1, -1);
}

bool solve(const std::vector<std::string> &S, const int &N) {
  auto start = find_start(S, N), end = find_end(S, N);
  if (start.first > end.first || start.second > end.second
      || start.first - end.first != start.second - end.second) {
    return false;
  }
  REP(i, N) {
    REP(j, N) {
      if (i < start.first || i > end.first || j < start.second || j > end.second) {
        if (S[i][j] == '#' || S[i][j] == '.') {
          return false;
        }
      }
    }
  }
  return true;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;
    std::vector<std::string> S(N);
    REP(i, N) {
      std::cin >> S[i];
    }
    printf("Case #%d: %s\n", t + 1, solve(S, N) ? "YES" : "NO");
  }

  return 0;
}
