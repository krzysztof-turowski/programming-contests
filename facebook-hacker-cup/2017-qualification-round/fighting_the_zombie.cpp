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

ldouble get_probability(const llong &X, const llong &Y, const llong &H) {
  if (H <= X) {
    return 1.0;
  }
  if (H > X * Y) {
    return 0.0;
  }

  vldouble D(H + 1, 0);
  if (Y <= H) {
    FOR(i, 1, Y) {
      D[i] = 1;
    }
  } else {
    FOR(i, 1, H - 1) {
      D[i] = 1;
    }
    D[H] = Y - H + 1;
  }

  REP(i, X - 1) {
    D[H] *= Y;
    FOR(j, 1, std::min(Y, H)) {
      D[H] += D[H - j] * (Y + 1 - j);
    }
    FORD(j, H - 1, 1) {
      D[j] = 0;
      FORD(k, j - 1, std::max(j - Y, 0L)) {
        D[j] += D[k];
      }
    }
  }

  ldouble out = D[H];
  REP(i, X) {
    out /= Y;
  }
  return std::max(out, D[H] / pow((ldouble)Y, (ldouble)X));
}

int main() {
  int T, S;
  llong X, Y, Z, H;
  std::string dice;
  std::cin >> T;
  REP(i, T) {
    std::cin >> H >> S;
    ldouble p = 0.0;
    REP(j, S) {
      std::cin >> dice;
      if (sscanf(dice.c_str(), "%lldd%lld+%lld", &X, &Y, &Z) < 3) {
        if (sscanf(dice.c_str(), "%lldd%lld-%lld", &X, &Y, &Z) < 3) {
          sscanf(dice.c_str(), "%lldd%lld", &X, &Y), Z = 0;
        } else {
          Z = -Z;
        }
      }
      p = std::max(p, get_probability(X, Y, H - Z));
    }
    printf("Case #%d: %.6Lf\n", i + 1, p);
  }
  return 0;
}
