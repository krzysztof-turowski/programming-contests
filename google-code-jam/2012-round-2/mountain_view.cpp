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

const int MAX = 10000000;

bool check(const int *Y, const int &A) {
  REP(i, A) FOR(j, i + 1, Y[i] - 1) {
    if (Y[j] > Y[i]) {
      return false;
    }
  }
  return true;
}

int main() {
  int T;
  std::cin >> T;

  REP(t, T) {
    int A;
    std::cin >> A, A--;

    int Y[A], X[A + 1], Z[A + 1];
    REP(i, A) {
      std::cin >> Y[i], Y[i]--;
    }
    if (check(Y, A)) {
      X[A] = MAX, Z[A] = -1;
      FORD(i, A - 1, 0) {
        Z[i] = Z[Y[i]] + 1, X[i] = X[Y[i]] - 1 - Z[i] * (Y[i] - i);
      }
      printf("Case #%d: ", t + 1);
      REP(i, A + 1) {
        printf("%d ", X[i]);
      }
      puts("");
    } else {
      printf("Case #%d: Impossible\n", t + 1);
    }
  }

  return 0;
}
