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

int war(const vdouble &A, const vdouble &B) {
  int index = 0, out = 0;
  REP(i, SIZE(A))   {
    while (B[index] < A[i] && index < SIZE(B))
      index++;
    if (index - i > out)
      out = index - i;
  }

  return out;
}

int deceitful_war(vdouble &A, vdouble &B) {
  int index = 0;
  REP(i, SIZE(A) - index)
    if (A[index + i] < B[i])
      index++, i--;

  return SIZE(A) - index;
}

int main() {
  int N;
  std::cin >> N;
  REP(t, N) {
    int T;
    std::cin >> T;

    vdouble A(T), B(T);
    REP(i, T)
      std::cin >> A[i];
    REP(i, T)
      std::cin >> B[i];
    std::sort(ALL(A)), sort(ALL(B));

    printf("Case #%d: %d %d\n", t + 1, deceitful_war(A, B), war(A, B));
  }

  return 0;
}
