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

void solve(std::string &A, std::string &low, std::string &high) {
  low = high = A;
  if (A.length() == 1) {
    return;
  }

  std::vector<int> right(10, -1);
  FORD(i, A.size() - 1, 0) {
    if (right[A[i] - '0'] < 0) {
      right[A[i] - '0'] = i;
    }
  }

  bool found = false;
  for (int i = 0; i < A.length() && !found; i++) {
    FORD(n, 9, A[i] - '0' + 1) {
      if (i < right[n]) {
        found = true;
        std::swap(high[i], high[right[n]]);
        break;
      }
    }
  }
  found = false;
  for (int i = 0; i < A.length() && !found; i++) {
    REP(n, A[i] - '0') {
      if (i < right[n] && (i != 0 || n != 0)) {
        found = true;
        std::swap(low[i], low[right[n]]);
        break;
      }
    }
  }
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    std::string N, low, high;
    std::cin >> N;
    solve(N, low, high);
    printf("Case #%d: %s %s\n", t + 1, low.c_str(), high.c_str());
  }

  return 0;
}
