#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

using llong = int64_t;
using ldouble = long double;
using vint = std::vector<int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

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
      int a = std::max_element(
          V.begin() + i, V.begin() + i + std::min(M - i, (E + R - 1) / R)) - V.begin();
      if (i == a) {
        U[i] = energy, energy = 0;
      } else if (energy + R * (a - i) > E) {
        int b = i;
        while (b < a && V[i] >= V[b]) {
          b++;
        }
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
    REP(i, M) {
      out += static_cast<llong>(V[i] * U[i]);
    }
    printf("Case #%d: %lld\n", t + 1, out);
  }

  return 0;
}
