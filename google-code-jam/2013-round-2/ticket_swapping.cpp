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

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<llong, llong> pllong;
typedef std::pair<double, double> pdouble;
typedef std::pair<ldouble, ldouble> pldouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;
typedef std::vector<std::string> vstring;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()
#define PART(c, k) c.begin(), c.begin() + (k)

#define ST first
#define ND second
#define INF 1000000000LL
#define INFL 1000000000000000000LL
#define EPS 1e-5
#define MAXVAL 1000002013

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

    FOREACH(it, stations) {
      if (it->second > 0) {
        current.push(std::make_pair(it->first, it->second));
        continue;
      }

      llong out = -it->second;
      while (out) {
        pllong &p = current.top();
        llong people = std::min(out, p.second);
        loss += ((calculate(p.first, it->first, N) % MAXVAL) * people) % MAXVAL, loss %= MAXVAL;

        p.second -= people, out -= people;
        if (p.second == 0)
          current.pop();
      }
    }
    printf("Case #%d: %lld\n", t + 1, gain >= loss ? gain - loss : gain + MAXVAL - loss);
  }

  return 0;
}
