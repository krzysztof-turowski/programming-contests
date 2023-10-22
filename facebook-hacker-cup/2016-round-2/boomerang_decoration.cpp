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

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const int INF = 1000000000;

bool are_identical(const std::string &A, const std::string &B, const int &x, const int &y) {
  FOR(i, x, y) {
    if (A[i] != B[i]) {
      return false;
    }
  }
  return true;
}

int solve() {
  int N;
  std::cin >> N;
  std::cin.ignore(INF, '\n');

  std::string left(N, '0'), right(N, '0');
  std::getline(std::cin, left);
  std::getline(std::cin, right);

  int x = 0, y = N - 1, counter = 0;
  while (x <= y) {
    if (are_identical(left, right, x, y)) {
      break;
    }
    x++, y--, counter++;
    while (right[x] == right[x - 1]) {
      x++;
    }
    while (right[y] == right[y + 1]) {
      y--;
    }
  }
  return counter;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %d\n", t + 1, solve());
  }
  return 0;
}
