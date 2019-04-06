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
#include <cassert>
#include <queue>

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
#define INFL 10000000000000LL
#define EPS 1e-5
#define MAX 100000

struct Barber {
  int index;
  llong time, speed;

  Barber(const int &index, const llong &speed) : index(index), time(0), speed(speed) { }

  bool operator< (const Barber& other) const {
    return time > other.time || (time == other.time && index > other.index);
  }
};

llong limit(const std::vector<Barber> &V, const llong &time) {
  llong out = 0;
  REP(i, SIZE(V))
    out += (time + V[i].speed  - 1) / V[i].speed;

  return out;
}

llong bisection(const std::vector<Barber> &V, llong low, llong high, const llong &N) {
  while (low + 1 != high) {
    llong mid = (low + high) / 2;
    if (limit(V, mid) >= N) {
      high = mid;
    } else {
      low = mid;
    }
  }

  return low;
}

int solve() {
  int B;
  llong N;
  std::cin >> B >> N;

  std::vector<Barber> V;
  int speed;
  REP(i, B)
    std::cin >> speed, V.push_back(Barber(i + 1, speed));

  llong time = INFL;
  REP(i, B)
    time = std::min(time, V[i].speed);
  time = bisection(V, 0, time * N, N);

  llong served = limit(V, time);
  N -= served;
  assert(N > 0);

  REP(i, B)
    V[i].time = time % V[i].speed;
  std::priority_queue<Barber, std::vector<Barber>> Q;
  REP(i, B)
    Q.push(V[i]);

  REP(i, N - 1) {
    Barber next = Q.top();
    Q.pop();

    next.time += next.speed;
    Q.push(next);
  }

  return Q.top().index;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %d\n", t + 1, solve());

  return 0;
}
