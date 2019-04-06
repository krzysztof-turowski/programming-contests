#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
  #define _USE_MATH_DEFINES
#endif

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef vint::iterator vit;
typedef std::vector<double> vdouble;
typedef vdouble::iterator vdit;
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
#define INF 1000000000
#define INFL 1000000000000000000LL
#define MOD 1000000007L
#define EPS 1e-5
#define MAX 10000001

bool primacity(int N) {
  int M = sqrt(N) + 1, K = 0;
  FOR(i, 2, M) {
    if (N % i == 0) {
      while (N % i == 0) {
        N /= i;
      }
      K++;
    }
    if (N == 1) {
      break;
    }
  }
  if (N > 1) {
    K++;
  }

  return K;
}

int solve(vint &data) {
  int A, B, K;
  std::cin >> A >> B >> K;

  if (K >= 9)
    return 0;

  int out = 0;
  FOR(i, A, B)
    if (data[i] == K)
      out++;

  return out;
}

int main() {
  int T;
  vint data(MAX), number(MAX);
  REP(i, MAX)
    number[i] = i;

  FOR(k, 2, sqrt(MAX) + 1) {
    if (data[k] == 0) {
      for (int i = k; i < MAX; i += k) {
        data[i]++;
        while (number[i] % k == 0) {
          number[i] /= k;
        }
      }
    }
  }
  REP(i, MAX)
    if (number[i] > 1)
      data[i]++;

  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %d\n", t + 1, solve(data));

  return 0;
}
