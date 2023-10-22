#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

void print(std::vector<char> &v, const int &R, const int &C) {
  v[0] = 'c';
  REP(i, R) {
    REP(j, C)
      printf("%c", v[i * C + j]);
    puts("");
  }
}

void check(std::vector<char> &v, const int &R, const int &C, const int &M, const int &F) {
  int m = 0, f = 0, x = 0;
  REP(i, R) REP(j, C) {
    if (v[i * C + j] == 'c') {
      x++;
    } else if (v[i * C + j] == '.') {
      f++;
    } else if (v[i * C + j] == '*') {
      m++;
    }
  }
  assert(x == 1);
  assert(f == F - 1);
  assert(m == M);
  assert(std::min(R, C) != 2 || M % 2 == 0);
  assert(std::min(R, C) < 3 || M != 5 || M != 7);
}

int bisection(const int &R, const int &C, const int &F) {
  int low = 1 + F % 2, high = R, length = C;
  while (low + 1 < high) {
    int value = (low + high + 1) / 2;
    if (value * length < F) {
      low = value;
    } else {
      high = value;
    }
  }
  return high;
}

bool solve(std::vector<char> &v, const int &R, const int &C, const int &F) {
  int r = bisection(R, C, F), c = bisection(C, r, F);
  int overflow = F - 2 * (r + c) + 4;

  if (overflow >= 0) {
    REP(i, r) REP(j, 2) {
      v[i * C + j] = '.';
    }
    REP(i, 2) REP(j, c) {
      v[i * C + j] = '.';
    }
    FOR(i, 2, r - 1) FOR(j, 2, c - 1) {
      if (overflow > 0) {
        v[i * C + j] = '.', --overflow;
      }
    }
    return true;
  }
  return false;
}

int main() {
  int N;
  std::cin >> N;
  REP(t, N) {
    int R, C, M, F;
    std::cin >> R >> C >> M, F = R * C - M;
    std::vector<char> data(R * C, '*');

    printf("Case #%d:\n", t + 1);
    if (F == 1) {
    } else if (R == 1 || C == 1) {
      REP(i, F) {
        data[i] = '.';
      }
    } else if (solve(data, R, C, F)) {
    } else {
      puts("Impossible");
      continue;
    }
    print(data, R, C);
    check(data, R, C, M, F);
  }

  return 0;
}
