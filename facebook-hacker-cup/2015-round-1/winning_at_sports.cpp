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

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

#define MAX 1000000007U
#define LENGTH 2001

int main() {
  int T;
  std::cin >> T;

  std::vector<unsigned> U[LENGTH], V[LENGTH];
  REP(i, LENGTH) {
    U[i].resize(LENGTH), V[i].resize(LENGTH);
  }
  REP(i, LENGTH) REP(j, LENGTH) {
    U[i][j] = V[i][j] = 0;
  }
  REP(i, LENGTH) {
    U[i][0] = V[0][i] = 1;
  }
  FOR(i, 1, LENGTH - 1) {
    FOR(j, i, LENGTH - 1) {
      U[j][i] = (U[j - 1][i] + U[j][i - 1]) % MAX;
    }
  }
  FOR(i, 1, LENGTH - 1) {
    FOR(j, i, LENGTH - 1) {
      V[i][j] = (V[i - 1][j] + V[i][j - 1]) % MAX;
    }
  }
  REP(t, T) {
    int A, B;
    scanf("%d-%d", &A, &B);
    printf("Case #%d: %u %u\n", t + 1, U[A - 1][B], V[B][B]);
  }

  return 0;
}
