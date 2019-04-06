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

class element {
 public:
  llong X, H;

  element() : X(0), H(0) { }
  element(llong X, llong H) : X(X), H(H) { }
};

class group_element {
 public:
  llong count, sum, sum_sq, H;

  explicit group_element(const llong &H) : count(0), sum(0), sum_sq(0), H(H) { }

  void add(const llong &X) {
    count++, sum = (sum + X) % MOD, sum_sq = (sum_sq + (X * X) % MOD) % MOD;
  }

  llong confont(const llong &X) {
    llong B2 = count * (X * X % MOD) % MOD;
    llong AB = MOD - (2 * (X * sum % MOD) % MOD);
    return (B2 + sum_sq + AB) % MOD;
  }
};

llong solve() {
  int N;
  std::cin >> N;

  std::vector<element> W(N);
  REP(i, N)
    std::cin >> W[i].X >> W[i].H;
  auto compare = [](element a, element b) { return a.X < b.X; };
  sort(ALL(W), compare);

  llong out = 0;
  std::list<group_element> L;
  REP(i, N) {
    while (!L.empty() && L.front().H < W[i].H)
      L.pop_front();
    if (!L.empty() && L.front().H == W[i].H) {
      out = (out + L.front().confont(W[i].X)) % MOD;
    } else {
      L.push_front(group_element(W[i].H));
    }
    L.front().add(W[i].X);
  }

  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %lld\n", t + 1, solve());

  return 0;
}
