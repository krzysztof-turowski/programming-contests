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

llong get_distance(pint &A, pint &B) {
  llong X = A.first - B.first, Y = A.second - B.second;
  return X * X + Y * Y;
}

llong solve() {
  int N;
  std::cin >> N;

  std::vector<pint> points(N);
  REP(i, N)
    std::cin >> points[i].ST >> points[i].ND;

  llong out = 0;
  REP(i, N) {
    vllong distances(N);
    REP(j, N)
      distances[j] = get_distance(points[i], points[j]);
    sort(distances.begin(), distances.end());
    int start = 0;
    while (start < N) {
      int end = start + 1;
      while (end < N && distances[end] == distances[start])
        end++;

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