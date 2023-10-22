#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <cassert>
#include <queue>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const llong INFL = 1000000000000000000LL;

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
  for (const auto &v : V) {
    out += (time + v.speed  - 1) / v.speed;
  }
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
  REP(i, B) {
    std::cin >> speed, V.push_back(Barber(i + 1, speed));
  }
  llong time = INFL;
  REP(i, B) {
    time = std::min(time, V[i].speed);
  }
  time = bisection(V, 0, time * N, N);

  llong served = limit(V, time);
  N -= served;
  assert(N > 0);

  REP(i, B) {
    V[i].time = time % V[i].speed;
  }
  std::priority_queue<Barber> Q;
  REP(i, B) {
    Q.push(V[i]);
  }

  REP(i, N - 1) {
    auto next = Q.top();
    Q.pop();

    next.time += next.speed;
    Q.push(next);
  }
  return Q.top().index;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %d\n", t + 1, solve());
  }
  return 0;
}
