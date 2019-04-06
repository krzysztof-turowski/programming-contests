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

ldouble get_remainder(llong low, llong high, vllong C) {
  if (low == high)
    return 0;

  ldouble remainder = (ldouble)(high * high - low * low) / 2;
  REP(i, SIZE(C))
    if (C[i] > high) {
      return remainder;
    } else if (C[i] <= low) {
      remainder -= (high - low) * C[i];
      low -= C[i];
      high -= C[i];
    } else {
      remainder -= (high - C[i]) * C[i];
      low = 0;
      high -= C[i];
    }

  return remainder;
}

ldouble solve() {
  int N;
  llong A, B, C_sum = 0;
  std::cin >> N >> A >> B;

  vllong C(N);
  REP(i, N)
    std::cin >> C[i], C_sum += C[i];

  ldouble remainder = 0;
  if (A / C_sum == B / C_sum) {
    remainder = get_remainder(A % C_sum, B % C_sum, C);
  } else {
    ldouble first = get_remainder(A % C_sum, C_sum, C);
    ldouble middle = get_remainder(0, C_sum, C);
    ldouble last = get_remainder(0, B % C_sum, C);
    remainder = first + (B / C_sum - A / C_sum - 1) * middle + last;
  }
  return remainder / (B - A);
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %.9Lf\n", t + 1, solve());

  return 0;
}
