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

struct food {
  int P, C, F;
};

bool solve(food &A, const std::vector<food> &data, const int &index) {
  if (A.P == 0 && A.C == 0 && A.F == 0)
    return true;
  if (index >= data.size())
    return false;
  if (solve(A, data, index + 1))
    return true;

  A.P -= data[index].P, A.C -= data[index].C, A.F -= data[index].F;
  if (A.P < 0 && A.C < 0 && A.F < 0)
    return false;
  return solve(A, data, index + 1);
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    food A;
    std::cin >> A.P >> A.C >> A.F;

    int N;
    std::cin >> N;
    std::vector<food> data(N);
    for (int i = 0; i < N; i++)
      std::cin >> data[i].P >> data[i].C >> data[i].F;

    printf("Case #%d: %s\n", t + 1, solve(A, data, 0) ? "yes" : "no");
  }

  return 0;
}
