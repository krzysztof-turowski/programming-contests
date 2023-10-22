#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <stack>
#include <map>

using llong = int64_t;
using ldouble = long double;
using pllong = std::pair<llong, llong>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const llong MAXVAL = 1000002013LL;

llong calculate(const int &start, const int &finish, const int &N) {
  llong k = finish - start;
  return k * (N + 1) - k * (k + 1) / 2;
}

int main() {
  int T, N, M;

  std::cin >> T;
  REP(t, T) {
    std::cin >> N >> M;

    std::map<llong, llong> stations;
    std::stack<pllong> current;
    llong gain = 0, loss = 0;
    REP(i, M) {
      int s, f, p;
      std::cin >> s >> f >> p;
      gain += ((calculate(s, f, N) % MAXVAL) * p) % MAXVAL, gain %= MAXVAL;
      stations[s] += p, stations[f] -= p;
    }

    for (auto [k, v] : stations) {
      if (v > 0) {
        current.push(std::make_pair(k, v));
        continue;
      }
      llong out = -v;
      while (out) {
        auto &p = current.top();
        llong people = std::min(out, p.second);
        loss += ((calculate(p.first, k, N) % MAXVAL) * people) % MAXVAL, loss %= MAXVAL;
        p.second -= people, out -= people;
        if (p.second == 0) {
          current.pop();
        }
      }
    }
    printf("Case #%d: %lld\n", t + 1, gain >= loss ? gain - loss : gain + MAXVAL - loss);
  }

  return 0;
}
