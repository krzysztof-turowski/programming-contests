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
#define MAX 10000

inline bool value(const int &a, const int &b) {
  return a > b;
}

double good(const int &N) {
  int p;
  double out = 0;
  vint A(N);

  REP(i, MAX) {
    REP(k, N)
      A[k] = k;
    REP(k, N)
      p = rand_r(NULL) % (N - k) + k, std::swap(A[k], A[p]);
    REP(k, N)
      out += value(A[k], k);
  }

  return out / MAX;
}

double bad(const int &N) {
  int p;
  double out = 0;
  vint A(N);

  REP(i, MAX) {
    REP(k, N)
      A[k] = k;
    REP(k, N)
      p = rand_r(NULL) % N, std::swap(A[k], A[p]);
    REP(k, N)
      out += value(A[k], k);
  }

  return out / MAX;
}

double score(const vint &A) {
  double out = 0;
  REP(i, SIZE(A))
    out += value(A[i], i);

  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;

    vint A(N);
    REP(i, N)
      std::cin >> A[i];

    double a = score(A), g = good(N), b = bad(N);

    printf("Case #%d: ", t + 1);
    if (fabs(a - g) < fabs(a - b))
      std::cout << "GOOD" << std::endl;
    else
      std::cout << "BAD" << std::endl;
  }

  return 0;
}
