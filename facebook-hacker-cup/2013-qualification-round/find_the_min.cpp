#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
  #define _USE_MATH_DEFINES
#endif

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
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef vint::iterator vit;
typedef std::vector<double> vdouble;
typedef vdouble::iterator vdit;
typedef std::vector<ldouble> vldouble;
typedef std::vector<std::string> vstring;
typedef std::vector<llong> vllong;
typedef std::vector<vint> graph;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ADD_EDGE(g, u, v) g[u].push_back(v), g[v].push_back(u)

#define ST first
#define ND second
#define INF 1000000000
#define INFL 1000000000000000000LL
#define MOD 1000000007L
#define EPS 1e-5

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
