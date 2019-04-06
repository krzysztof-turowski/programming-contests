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
#define PB push_back
#define INF 1000000000LL
#define EPS 1e-5

void pick(vint &A) {
  int n, a;

  std::cin >> n;
  REP(i, 4 * (n - 1))
    std::cin >> a;
  REP(i, 4)
    std::cin >> A[i];
  REP(i, 4 * (4 - n))
    std::cin >> a;
  std::sort(ALL(A));
}

int main() {
  int N;
  std::cin >> N;
  REP(t, N) {
    vint A(4), B(4), C(4);
    pick(A), pick(B);

    int out = std::set_intersection(ALL(A), ALL(B), C.begin()) - C.begin();
    if (out == 0) {
      printf("Case #%d: Volunteer cheated!\n", t + 1);
    } else if (out == 1) {
      printf("Case #%d: %d\n", t + 1, C[0]);
    } else {
      printf("Case #%d: Bad magician!\n", t + 1);
    }
  }

  return 0;
}
