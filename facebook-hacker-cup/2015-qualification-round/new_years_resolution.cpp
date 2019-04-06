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

struct food {
  int P, C, F;
};

bool solve(food &A, const std::vector<food> &data, const int &index) {
  if (A.P == 0 && A.C == 0 && A.F == 0)
    return true;
  if (index >= data.size())
    return false;
  if (solve(A, data, index + 1))
    return true;

  A.P -= data[index].P, A.C -= data[index].C, A.F -= data[index].F;
  if (A.P < 0 && A.C < 0 && A.F < 0)
    return false;
  return solve(A, data, index + 1);
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    food A;
    std::cin >> A.P >> A.C >> A.F;

    int N;
    std::cin >> N;
    std::vector<food> data(N);
    for (int i = 0; i < N; i++)
      std::cin >> data[i].P >> data[i].C >> data[i].F;

    printf("Case #%d: %s\n", t + 1, solve(A, data, 0) ? "yes" : "no");
  }

  return 0;
}
