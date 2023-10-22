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

struct vine {
  llong position, length;
};

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int A;
    std::cin >> A;

    std::vector<struct vine> X(A);
    REP(i, A) {
      std::cin >> X[i].position >> X[i].length;
    }
    llong D;
    std::cin >> D;

    bool found = false;
    vllong range(A, 0);
    range[0] = 2 * X[0].position;
    if (range[0] >= D) {
      found = true;
    } else {
      FOR(i, 1, A - 1) FORD(j, i - 1, 0) {
        if (range[j] >= X[i].position) {
          llong value = X[i].position + std::min(X[i].position - X[j].position, X[i].length);
          if (value > range[i]) {
            range[i] = value;
          }
          if (value >= D) {
            found = true;
          }
        }
      }
      if (found) {
        break;
      }
    }
    printf("Case #%d: %s\n", t + 1, found ? "YES" : "NO");
  }

  return 0;
}
