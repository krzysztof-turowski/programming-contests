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

struct node {
  int minsum, rcolor, ncolor, delta;
  vint child;
};

std::vector<node> T;

int recursion(const int &i) {
  if (SIZE(T[i].child) == 0) {
    T[i].ncolor = 2;
    return T[i].minsum = T[i].rcolor = T[i].delta = 1;
  }

  int mintotal = 0;
  vint coloradd(SIZE(T[i].child) + 3);
  REP(j, SIZE(coloradd))
    coloradd[j] = j;
  FOREACH(child, T[i].child)
    mintotal += recursion(*child), coloradd[T[*child].rcolor] += T[*child].delta;

  int sum1 = INF, sum2 = INF, color1 = INF, color2 = INF;
  FOR(j, 1, SIZE(coloradd) - 1) {
    int value = coloradd[j];
    if (value < sum1) {
      color2 = color1, sum2 = sum1, color1 = j, sum1 = value;
    } else if (value < sum2) {
      color2 = j, sum2 = value;
    }
  }

  T[i].rcolor = color1;
  T[i].delta = sum2 - sum1;
  T[i].ncolor = color2;
  return T[i].minsum = sum1 + mintotal;
}

int solve() {
  int N;
  std::cin >> N;

  T.clear(), T.resize(N);
  REP(i, N) {
    int a;
    std::cin >> a;

    if (a > 0)
      T[a - 1].child.push_back(i);
  }

  return recursion(0);
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %d\n", t + 1, solve());

  return 0;
}
