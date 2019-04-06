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

int solve(const vllong &A, const vllong &B, const int &N, const int &shift) {
  llong x = A[0] ^ B[shift];

  vllong C(N);
  REP(i, N)
    C[i] = B[i] ^ x;
  sort(ALL(C));

  REP(i, N)
    if (A[i] != C[i])
      return INF;

  int out = 0;
  while (x) {
    if (x % 2)
      out++;
    x >>= 1;
  }

  return out;
}

llong convert(const std::string &x) {
  llong out = 0ULL;
  REP(i, SIZE(x))
    if (x[i] == '1')
      out ^= (1ULL << i);

  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N, L;
    std::cin >> N >> L;

    std::string x;
    vllong A(N), B(N);
    REP(i, N)
      std::cin >> x, A[i] = convert(x);
    REP(i, N)
      std::cin >> x, B[i] = convert(x);

    std::sort(ALL(A));
    int out = INF;
    REP(i, N)
      out = std::min(out, solve(A, B, N, i));

    printf("Case #%d: ", t + 1);
    if (out <= L) {
      std::cout << out << std::endl;
    } else {
      std::cout <<  "NOT POSSIBLE" << std::endl;
    }
  }

  return 0;
}
