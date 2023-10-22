#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int S, A = 0, B = 0;
    std::string V;
    std::cin >> S >> V;
    REP(i, S + 1) {
      if (A + B < i)
        B++;
      A += V[i] - '0';
    }
    printf("Case #%d: %d\n", t + 1, B);
  }

  return 0;
}
