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

bool solve() {
  int N;
  std::cin >> N;

  std::deque<int> A(N), B;
  REP(i, N)
    std::cin >> A[i];

  int low, high;

  low = 1, high = N - 1;
  B.push_back(A[0]);
  REP(i, N - 1)
    if (A[low] == B.front() - 1)
      B.push_front(A[low]), low++;
    else if (A[low] == B.back() + 1)
      B.push_back(A[low]), low++;
    else if (A[high] == B.front() - 1)
      B.push_front(A[high]), high--;
    else if (A[high] == B.back() + 1)
      B.push_back(A[high]), high--;
    else
      break;

  if (B.size() == N)
    return true;
  B.clear();

  low = 0, high = N - 2;
  B.push_back(A[N - 1]);
  REP(i, N - 1)
    if (A[low] == B.front() - 1)
      B.push_front(A[low]), low++;
    else if (A[low] == B.back() + 1)
      B.push_back(A[low]), low++;
    else if (A[high] == B.front() - 1)
      B.push_front(A[high]), high--;
    else if (A[high] == B.back() + 1)
      B.push_back(A[high]), high--;
    else
      break;

  return B.size() == N;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d: %s\n", t + 1, solve() ? "yes" : "no");

  return 0;
}
