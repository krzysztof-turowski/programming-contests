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
  llong time, endtime;

  explicit element(const llong &time) : time(time), endtime(time) { }
  element(const llong &time, const llong &endtime) : time(time), endtime(endtime) { }
};

llong solve() {
  llong L, N, M, D;
  std::cin >> L >> N >> M >> D;

  vllong W(N);
  REP(i, N)
    std::cin >> W[i];
  sort(ALL(W));

  auto compare = [](element a, element b) { return a.endtime > b.endtime; };
  std::priority_queue<element, std::vector<element>, decltype(compare)> Q(compare);
  REP(i, std::min(L, N))
    Q.push(element(W[i]));

  vllong washed(L), dryed(std::min(M, L), 0L);
  REP(i, L) {
    element machine = Q.top();
    dryed[i % M] = std::max(dryed[i % M], machine.endtime) + D;
    Q.pop(), Q.push(element(machine.time, machine.endtime + machine.time));
  }
  return *std::max_element(ALL(dryed));
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %lld\n", t + 1, solve());

  return 0;
}
