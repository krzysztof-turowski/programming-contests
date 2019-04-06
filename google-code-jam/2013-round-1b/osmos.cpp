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
typedef std::vector<llong> vllong;
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

int main() {
  int T, M;
  std::cin >> T;
  REP(t, T) {
    llong A;
    std::cin >> A >> M;
    vllong B(M);
    REP(i, M)
      std::cin >> B[i];
    std::sort(ALL(B));

    int value = 0, out = INF;
    if (A > 1) {
      REP(i, M) {
        if (A <= B[i]) {
          out = std::min(out, value + M - i);
          while (A <= B[i])
            A = 2 * A - 1, value++;
        }
        A += B[i];
      }
    } else {
      value = M;
    }
    printf("Case #%d: %d\n", t + 1, std::min(out, value));
  }

  return 0;
}
