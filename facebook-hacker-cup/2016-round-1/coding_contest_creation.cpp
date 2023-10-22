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
using vint = std::vector<int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int split(vint D, int low, int high) {
  int count = 1, out = 0, index = low + 1;

  while (index <= high) {
    if (D[index] <= D[index - 1] + 10) {
      index++;
    } else {
      D[index - 1] += 10, out++;
    }
    count++;

    if (count == 4) {
      if (index > high) {
        break;
      }
      count = 1, index++;
    }
  }
  return out + (4 - count);
}

int solve() {
  int N;
  std::cin >> N;

  vint D(N);
  REP(i, N) {
    std::cin >> D[i];
  }
  int low = 0, out = 0;
  FOR(i, 1, N - 1) {
    if (D[i] <= D[i - 1]) {
      out += split(D, low, i - 1), low = i;
    }
  }
  out += split(D, low, N - 1);
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %d\n", t + 1, solve());

  return 0;
}
