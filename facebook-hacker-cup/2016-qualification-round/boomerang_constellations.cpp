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

typedef int64_t llong;
typedef std::pair<int, int> pint;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

llong get_distance(pint &A, pint &B) {
  llong X = A.first - B.first, Y = A.second - B.second;
  return X * X + Y * Y;
}

llong solve() {
  int N;
  std::cin >> N;

  std::vector<pint> points(N);
  REP(i, N) {
    std::cin >> points[i].first >> points[i].second;
  }
  llong out = 0;
  REP(i, N) {
    std::vector<llong> distances(N);
    REP(j, N) {
      distances[j] = get_distance(points[i], points[j]);
    }
    std::sort(distances.begin(), distances.end());
    int start = 0;
    while (start < N) {
      int end = start + 1;
      while (end < N && distances[end] == distances[start]) {
        end++;
      }
      llong repeats = end - start;
      out += repeats * (repeats - 1) / 2;
      start = end;
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %lld\n", t + 1, solve());
  }
  return 0;
}
