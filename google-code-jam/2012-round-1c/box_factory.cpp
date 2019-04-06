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
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;
typedef std::vector<llong> vllong;

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

llong solve(const vllong &a, const vint &A, const vllong &b, const vint &B) {
  int N = SIZE(A), M = SIZE(B);
  std::vector<vllong> C(N + 1);
  vllong suma(N + 1), sumb(M + 1);
  REP(i, N + 1)
    C[i].resize(M + 1);

  FOR(i, 1, N) FOR(j, 1, M) {
    if (A[i - 1] == B[j - 1]) {
      suma[i] = 0, sumb[j] = 0;
      FORD(k, i - 1, 0)
        suma[k] = suma[k + 1] + (A[k] == A[i - 1] ? a[k] : 0);
      FORD(k, j - 1, 0)
        sumb[k] = sumb[k + 1] + (B[k] == B[j - 1] ? b[k] : 0);

      REP(k, i)
        REP(l, j)
          C[i][j] = std::max(C[i][j], C[k][l] + std::min(suma[k], sumb[l]));
    } else {
      C[i][j] = std::max(C[i - 1][j], C[i][j - 1]);
    }
  }

  return C[N][M];
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N, M;
    vllong a, b;
    vint A, B;

    std::cin >> N >> M;
    a.resize(N), A.resize(N), b.resize(M), B.resize(M);
    REP(i, N)
      std::cin >> a[i] >> A[i];
    REP(i, M)
      std::cin >> b[i] >> B[i];

    printf("Case #%d: %lld\n", t + 1, solve(a, A, b, B));
  }

  return 0;
}
