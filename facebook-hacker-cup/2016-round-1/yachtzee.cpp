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
using vllong = std::vector<llong>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

ldouble get_remainder(llong low, llong high, vllong C) {
  if (low == high) {
    return 0;
  }
  ldouble remainder = static_cast<ldouble>(high * high - low * low) / 2;
  REP(i, SIZE(C)) {
    if (C[i] > high) {
      return remainder;
    }
    if (C[i] <= low) {
      remainder -= (high - low) * C[i];
      low -= C[i];
      high -= C[i];
    } else {
      remainder -= (high - C[i]) * C[i];
      low = 0;
      high -= C[i];
    }
  }
  return remainder;
}

ldouble solve() {
  int N;
  llong A, B, C_sum = 0;
  std::cin >> N >> A >> B;

  vllong C(N);
  REP(i, N) {
    std::cin >> C[i], C_sum += C[i];
  }
  ldouble remainder = 0;
  if (A / C_sum == B / C_sum) {
    remainder = get_remainder(A % C_sum, B % C_sum, C);
  } else {
    ldouble first = get_remainder(A % C_sum, C_sum, C);
    ldouble middle = get_remainder(0, C_sum, C);
    ldouble last = get_remainder(0, B % C_sum, C);
    remainder = first + (B / C_sum - A / C_sum - 1) * middle + last;
  }
  return remainder / (B - A);
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %.9Lf\n", t + 1, solve());
  }
  return 0;
}
