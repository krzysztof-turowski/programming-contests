#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using ldouble = long double;
using vstring = std::vector<std::string>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

const char dir[4] = { '>', '<', '^', 'v' };

bool check(const vstring &A, const char &direction, const int &x, const int &y) {
  if (direction == '>') {
    FOR(i, y + 1, SIZE(A[x]) - 1) {
      if (A[x][i] != '.') {
        return true;
      }
    }
  } else if (direction == '<') {
    FORD(i, y - 1, 0) {
      if (A[x][i] != '.') {
        return true;
      }
    }
  } else if (direction == '^') {
    FORD(i, x - 1, 0) {
      if (A[i][y] != '.') {
        return true;
      }
    }
  } else {
    FOR(i, x + 1, SIZE(A) - 1) {
      if (A[i][y] != '.') {
        return true;
      }
    }
  }
  return false;
}

int solve() {
  int R, C;
  std::cin >> R >> C;

  vstring A(R);
  REP(i, R) {
    std::cin >> A[i];
  }
  int out = 0;
  REP(i, R) REP(j, C) {
    if (A[i][j] != '.' && !check(A, A[i][j], i, j)) {
      int dirs = 0;
      REP(k, 4)
        dirs += check(A, dir[k], i, j);
      if (dirs == 0)
        return -1;
      out++;
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: ", t + 1);
    int out = solve();
    out >= 0 ? printf("%d\n", out) : puts("IMPOSSIBLE");
  }

  return 0;
}
