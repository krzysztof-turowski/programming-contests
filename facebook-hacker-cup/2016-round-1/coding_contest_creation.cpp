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

int split(vint D, int low, int high) {
  int count = 1, out = 0, index = low + 1;

  while (index <= high) {
    if (D[index] <= D[index - 1] + 10)
      index++;
    else
      D[index - 1] += 10, out++;
    count++;

    if (count == 4) {
      if (index > high)
        break;
      count = 1, index++;
    }
  }
  return out + (4 - count);
}

int solve() {
  int N;
  std::cin >> N;

  vint D(N);
  REP(i, N)
    std::cin >> D[i];

  int low = 0, out = 0;
  FOR(i, 1, N - 1) {
    if (D[i] <= D[i - 1]) {
      out += split(D, low, i - 1);
      low = i;
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
