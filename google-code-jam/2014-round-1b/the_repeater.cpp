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
#define MAX 101

void shorten(const std::string &s, std::pair<std::string, vint> &d) {
  d.ST = s.substr(0, 1), d.ND.PB(1);
  REP(i, SIZE(s) - 1)
    if (s[i] != s[i + 1])
      d.ST += s.substr(i + 1, 1), d.ND.PB(1);
    else
      ++d.ND.back();
}

llong solve(const vstring &S, const int &N) {
  std::vector<std::pair<std::string, vint> > D(N);

  REP(i, N)
    shorten(S[i], D[i]);

  REP(i, N)
    FOR(j, i + 1, N - 1)
      if (D[i].ST != D[j].ST)
        return INF;

  llong out = 0;
  REP(i, SIZE(D[0].ND)) {
    llong low = INF;
    REP(j, MAX) {
      llong sum = 0;
      REP(k, N)
        sum += std::max(D[k].ND[i] - j, j - D[k].ND[i]);
      low = std::min(low, sum);
    }
    out += low;
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;

    vstring S(N);
    REP(i, N)
      std::cin >> S[i];

    int out = solve(S, N);
    if (out == INF) {
      printf("Case #%d: Fegla Won\n", t + 1);
    } else {
      printf("Case #%d: %d\n", t + 1, out);
    }
  }

  return 0;
}
