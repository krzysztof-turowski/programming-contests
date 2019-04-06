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
#define MAX_PLAYERS 16

std::set<int> FORBIDDEN_STATES{2, 4, 8, 16};

bool wins_with_any(const std::vector<vint> &A, const int &state, const int &index) {
  REP(i, MAX_PLAYERS)
    if (i != index && (state & (1 << i)) && A[index][i])
      return true;
  return false;
}

bool wins_with_all(const std::vector<vint> &A, const int &state, const int &index) {
  REP(i, MAX_PLAYERS)
    if (i != index && (state & (1 << i)) && !A[index][i])
      return false;
  return true;
}

void state_to_indices(const int &state, vint &indices) {
  REP(i, MAX_PLAYERS)
    if (state & (1 << i))
      indices.push_back(i);
}

int indices_to_state(const vint &indices, const int &mask) {
  int state = 0;
  REP(i, SIZE(indices))
    if (mask & (1 << i))
      state |= (1 << indices[i]);
  return state;
}

int get_ones(const int &state) {
  int out = 0;
  REP(i, MAX_PLAYERS)
    if (state & (1 << i))
      out++;
  return out;
}

void get_scores(const std::vector<vint> &A, std::vector<vint> &can_win, vint &toursize) {
  REP(i, SIZE(A))
    can_win[1 << i][i] = 1;

  REP(i, SIZE(can_win)) {
    int ones_in_state = get_ones(i);
    if (FORBIDDEN_STATES.count(ones_in_state) == 0)
      continue;

    vint all_players;
    state_to_indices(i, all_players);
    REP(j, 1 << ones_in_state) {
      int first = indices_to_state(all_players, j);
      int second = indices_to_state(all_players, ~j);
      assert((first | second) == i && (first & second) == 0);

      REP(w_1, SIZE(A))
        if (can_win[first][w_1]) {
          REP(w_2, SIZE(A))
            if (can_win[second][w_2]) {
              int w = A[w_1][w_2] ? w_1 : w_2;
              can_win[i][w] = true;
              toursize[w] = std::max(toursize[w], ones_in_state);
            }
        }
    }
  }
}

void solve() {
  int N;
  std::cin >> N;

  std::vector<vint> A(N, vint(N));
  REP(i, N) REP(j, N)
    std::cin >> A[i][j];

  std::vector<vint> can_win(1 << N, vint(N, false));
  vint toursize(N, 1);
  get_scores(A, can_win, toursize);

  REP(i, N)
    std::cout << N / (2 * toursize[i]) + 1 << " "
        << (wins_with_all(A, (1 << N) - 1, i) ? 1 : (N / 2 + 1)) << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)
    printf("Case #%d:\n", t + 1), solve();

  return 0;
}
