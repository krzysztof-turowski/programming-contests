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
using vllong = std::vector<llong>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const int INF = 1000000000;

int main() {
  int T, M;
  std::cin >> T;
  REP(t, T) {
    llong A;
    std::cin >> A >> M;
    vllong B(M);
    REP(i, M) {
      std::cin >> B[i];
    }
    std::sort(B.begin(), B.end());

    int value = 0, out = INF;
    if (A > 1) {
      REP(i, M) {
        if (A <= B[i]) {
          out = std::min(out, value + M - i);
          while (A <= B[i])
            A = 2 * A - 1, value++;
        }
        A += B[i];
      }
    } else {
      value = M;
    }
    printf("Case #%d: %d\n", t + 1, std::min(out, value));
  }

  return 0;
}
