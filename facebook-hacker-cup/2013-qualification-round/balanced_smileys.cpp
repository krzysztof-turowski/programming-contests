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

int main() {
  int T;
  std::string text;

  std::cin >> T, std::getline(std::cin, text);
  REP(t, T) {
    std::getline(std::cin, text);
    int min = 0, max = 0;
    REP(i, text.length())
      if (text[i] == '(') {
        max++;
        if (i == 0 || text[i - 1] != ':')
          min++;
      } else if (text[i] == ')') {
        min = min ? min - 1 : 0;
        if (i == 0 || text[i - 1] != ':')
          max--;
        if (max < 0)
          break;
      }

    printf("Case #%d: %s\n", t + 1, (max >= 0) && (min == 0) ? "YES" : "NO");
  }

  return 0;
}
