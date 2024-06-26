#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

llong max_position(const llong &p, const llong &l, const llong &v, const llong &k) {
  if (k == 0) {
    return p;
  }
  if (k == l - 1) {
    return p + l - 1;
  }
  return max_position(p, l / 2, v, (k + 1) / 2);
}

llong max_binary(const llong &L, const llong &P) {
  llong low = 0, high = L - 1, mid;
  while (low + 1 != high) {
    mid = (low + high) / 2;
    if (max_position(0, L, mid, mid) < P) {
      low = mid;
    } else {
      high = mid;
    }
  }
  return low;
}

llong min_position(const llong &p, const llong &l, const llong &v, const llong &k) {
  if (k == 0) {
    return p;
  }
  if (k == l - 1) {
    return p + l - 1;
  }
  return min_position(p + l / 2, l / 2, v, (k - 1) / 2);
}

llong min_binary(const llong &L, const llong &P) {
  llong low = 0, high = L - 1, mid;
  while (low + 1 != high) {
    mid = (low + high) / 2;
    if (min_position(0, L, mid, mid) < P) {
      low = mid;
    } else {
      high = mid;
    }
  }
  return low;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    llong N, P, L;
    std::cin >> N >> P;
    L = 1LL << N;
    llong a = P == L ? L - 1 : min_binary(L, P), b = P == L ? L - 1 : max_binary(L, P);
    printf("Case #%d: %lld %lld\n", t + 1, a, b);
  }
  return 0;
}
