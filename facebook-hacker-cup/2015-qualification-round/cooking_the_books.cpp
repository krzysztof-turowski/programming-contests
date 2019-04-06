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
#define MAX 100000

void solve(std::string &A, std::string &low, std::string &high) {
  low = high = A;
  if (A.length() == 1)
    return;

  vint right(10, -1);
  FORD(i, SIZE(A) - 1, 0)
    if (right[A[i] - '0'] < 0)
      right[A[i] - '0'] = i;

  bool found = false;
  for (int i = 0; i < A.length() && !found; i++)
    FORD(n, 9, A[i] - '0' + 1)
      if (i < right[n]) {
        found = true;
        std::swap(high[i], high[right[n]]);
        break;
      }

  found = false;
  for (int i = 0; i < A.length() && !found; i++)
    REP(n, A[i] - '0')
      if (i < right[n] && (i != 0 || n != 0)) {
        found = true;
        std::swap(low[i], low[right[n]]);
        break;
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
