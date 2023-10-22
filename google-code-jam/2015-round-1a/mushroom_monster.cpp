#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using vllong = std::vector<llong>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

llong solve_any(const vllong &M) {
  llong out = 0;
  REP(i, SIZE(M) - 1) {
    out += std::max(M[i] - M[i + 1], 0L);
  }
  return out;
}

llong solve_fixed(const vllong &M) {
  llong size = 0, out = 0;
  REP(i, SIZE(M) - 1) {
    size = std::max(M[i] - M[i + 1], size);
  }
  REP(i, SIZE(M) - 1) {
    out += std::min(size, M[i]);
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;
    vllong M(N);
    REP(i, N) {
      std::cin >> M[i];
    }
    printf("Case #%d: %lld %lld\n", t + 1, solve_any(M), solve_fixed(M));
  }

  return 0;
}
