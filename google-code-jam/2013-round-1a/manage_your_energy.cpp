#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::pair<ldouble, ldouble> pldouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;

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

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int E, R, M;
    std::cin >> E >> R >> M;
    R = std::min(E, R);

    vint V(M), U(M);
    REP(i, M)
      std::cin >> V[i];

    int energy = E;
    REP(i, M) {
      int a =
          std::max_element(V.begin() + i, V.begin() + i + std::min(M - i, (E + R - 1) / R))
              - V.begin();
      if (i == a) {
        U[i] = energy, energy = 0;
      } else if (energy + R * (a - i) > E) {
        int b = i;
        while (b < a && V[i] >= V[b])
          b++;
        if (b == a) {
          int left = std::max(0, E - R * (a - i));
          U[i] = energy - left, energy = left;
        } else if (energy + R * (b - i) > E) {
          int left = std::max(0, E - R * (b - i));
          U[i] = energy - left, energy = left;
        }
      }
      energy = std::min(energy + R, E);
    }

    llong out = 0;
    REP(i, M)
      out += static_cast<llong>(V[i] * U[i]);
    printf("Case #%d: %lld\n", t + 1, out);
  }

  return 0;
}
