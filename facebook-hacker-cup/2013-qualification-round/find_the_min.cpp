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

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int main() {
  int N;
  std::cin >> N;

  REP(t, N) {
    int n, k, a, b, c, r;
    std::cin >> n >> k >> a >> b >> c >> r;

    std::vector<int> values(k), indices(k + 1);
    values[0] = a;
    REP(i, k - 1)
      values[i + 1] = (b * static_cast<llong>(values[i]) + c) % r;

    std::set<int> allowed;
    FOR(i, 0, k)
      allowed.insert(i);
    REP(i, k)
      if (values[i] <= k)
        allowed.erase(values[i]), indices[values[i]] = i + k;

    if (n > 2 * k)
      n = k + (n + 1) % (k + 1);
    FOR(i, k, n - 2) {
      int value = *(allowed.begin());
      indices[value] = i + k;
      if (value <= k)
        allowed.erase(value);

      if (values[i % k] <= k && indices[values[i % k]] <= i)
        allowed.insert(values[i % k]);
      values[i % k] = value;
    }

    printf("Case #%d: %d\n", t + 1, *(allowed.begin()));
  }

  return 0;
}
