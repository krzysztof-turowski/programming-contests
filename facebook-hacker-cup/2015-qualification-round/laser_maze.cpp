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

int LR[] = {-1, 1, 0, 0}, UD[] = {0, 0, -1, 1};

bool is_visible(
    const vstring &P, const int &p, const int &q, const int &a, const int &b, const int &dir) {
  if (dir == 0 && p == a && b > q) {
    FORD(i, b - 1, q)
      if (P[p][i] != '.')
        return false;
    return true;
  } else if (dir == 1 && q == b && a > p) {
    FORD(i, a - 1, p)
      if (P[i][q] != '.')
        return false;
    return true;
  } else if (dir == 2 && p == a && b < q) {
    FOR(i, b + 1, q)
      if (P[p][i] != '.')
        return false;
    return true;
  } else if (dir == 3 && q == b && a < p) {
    FOR(i, a + 1, p)
      if (P[i][q] != '.')
        return false;
    return true;
  }

  return false;
}

bool is_available(
    vstring &P, const int &p, const int &q, const int &move, std::map<char, int> &dir) {
  if (P[p][q] != '.')
    return false;

  REP(i, SIZE(P))
    REP(j, SIZE(P[i]))
      if (P[i][j] == '<' || P[i][j] == '^' || P[i][j] == '>' || P[i][j] == 'v')
        if (is_visible(P, p, q, i, j, (dir[P[i][j]] + move) % 4))
          return false;
  return true;
}

int solve(vstring &P, const int &ps, const int &qs, const int &pg, const int &qg) {
  std::map<char, int> dir;
  dir['<'] = 0, dir['^'] = 1, dir['>'] = 2, dir['v'] = 3;

  std::vector<std::vector<vint> > A(4);
  REP(k, 4) {
    A[k].resize(SIZE(P));
    REP(i, SIZE(P)) {
      A[k][i].resize(SIZE(P[i]));
      REP(j, SIZE(P[i]))
        A[k][i][j] = INF;
    }
  }

  // Dijkstra
  std::queue<std::pair<int, pint> > Q;
  Q.push(std::make_pair(0, std::make_pair(ps, qs)));

  while (!Q.empty()) {
    std::pair<int, pint> top = Q.front();
    int move = top.first, p = top.second.first, q = top.second.second;
    Q.pop();

    if (p == pg && q == qg)
      return move;
    if (A[move % 4][p][q] != INF)
      continue;
    A[move % 4][p][q] = move;

    if (p > 0 && is_available(P, p - 1, q, move + 1, dir))
      Q.push(std::make_pair(move + 1, std::make_pair(p - 1, q)));
    if (q > 0 && is_available(P, p, q - 1, move + 1, dir))
      Q.push(std::make_pair(move + 1, std::make_pair(p, q - 1)));
    if (p < SIZE(P) - 1 && is_available(P, p + 1, q, move + 1, dir))
      Q.push(std::make_pair(move + 1, std::make_pair(p + 1, q)));
    if (q < SIZE(P[p]) - 1 && is_available(P, p, q + 1, move + 1, dir))
      Q.push(std::make_pair(move + 1, std::make_pair(p, q + 1)));
  }

  return 0;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int M, N;
    std::cin >> M >> N;

    vstring P(M);
    for (int i = 0; i < M; i++)
      std::cin >> P[i];

    int ps, qs, pg, qg;
    REP(i, SIZE(P))
      REP(j, SIZE(P[i]))
        if (P[i][j] == 'S')
          ps = i, qs = j, P[i][j] = '.';
        else if (P[i][j] == 'G')
          pg = i, qg = j, P[i][j] = '.';

    int value = solve(P, ps, qs, pg, qg);
    if (value > 0) {
      printf("Case #%d: %d\n", t + 1, value);
    } else {
      printf("Case #%d: impossible\n", t + 1);
    }
  }

  return 0;
}
