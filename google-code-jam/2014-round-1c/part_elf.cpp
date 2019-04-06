#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;
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
#define INF 1000000000LL
#define EPS 1e-5
#define MAX 101

llong gcd(const llong &P, const llong &Q) {
  if (P == 0)
    return Q;
  return gcd(Q % P, P);
}

int solve(llong &P, llong &Q) {
  llong X = gcd(P, Q);
  P /= X, Q /= X;

  bool possible = false;
  FOR(i, 1, 40)
    if (Q == (1ULL << i))
      possible = true;

  if (possible)
    FOR(i, 1, 40)
      if (Q <= P * (1ULL << i))
        return i;
  return INF;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    llong P, Q;
    scanf("%llu/%llu", &P, &Q);

    printf("Case #%d: ", t + 1);
    int out = solve(P, Q);
    if (out == INF) {
      std::cout << "impossible" << std::endl;
    } else {
      std::cout << out << std::endl;
    }
  }

  return 0;
}
