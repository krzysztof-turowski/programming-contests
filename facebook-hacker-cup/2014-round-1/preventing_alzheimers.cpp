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

int N_SMALL = 15, N_LARGE = 20, MAX_LARGE = 152;
vint SMALL = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
vint LARGE = {53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
              127, 131, 137, 139, 149, 151};
int MAX = 1000000000;

int mask(const int &v) {
  int out = 0;
  for (int i = 0; i < N_SMALL; i++) {
    if (v % SMALL[i] == 0) {
      out |= (1 << i);
    }
  }
  return out;
}

int hit(const int &v) {
  int out = 0;
  for (int i = 0; i < N_LARGE; i++) {
    if (v % LARGE[i] == 0) {
      return i;
    }
  }
  return -1;
}

int solve(const vint &A, const int &K, const vint &MASK, const vint &USED) {
  vint V;
  int start = 0, zeros = 0, maximum = 0;
  for (int i = 0; i < A.size(); i++) {
    maximum = std::max(maximum, A[i]);
    if (A[i] > K) {
      V.push_back(A[i]);
    } else {
      start += K - A[i];
    }
    if (A[i] == 0) {
      zeros++;
    }
  }
  if (maximum <= K) {
    return start - (zeros > 0) * K;
  }
  std::vector<std::vector<vint>> state(
      V.size() + 1, std::vector<vint>(1 << N_SMALL, vint(N_LARGE + 1, MAX)));
  state[0][0][0] = start;
  for (int i = 0; i < V.size(); i++) {
    for (int mask = 0; mask < (1 << N_SMALL); mask++) {
      for (int j = 0; j <= i + 1; j++) {
        if (state[i][mask][j] == MAX) {
          continue;
        }
        for (int v = (V[i] + K - 1) / K; v <= LARGE[j]; v++) {
          if (mask & MASK[v]) {
            continue;
          }
          if (USED[v] >= 0 && USED[v] < j) {
            continue;
          }
          int m = mask | MASK[v], k = USED[v] >= 0 ? USED[v] + 1 : j;
          state[i + 1][m][k] = std::min(
              state[i + 1][m][k], state[i][mask][j] + v * K - V[i]);
        }
      }
    }
  }
  int out = MAX;
  for (int mask = 0; mask < (1 << N_SMALL); mask++) {
    for (int i = 0; i <= N_LARGE; i++) {
      out = std::min(out, state[V.size()][mask][i]);
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  vint MASK(MAX_LARGE), USED(MAX_LARGE);
  for (int i = 0; i < MAX_LARGE; i++) {
    MASK[i] = mask(i), USED[i] = hit(i);
  }
  REP(t, T) {
    int N, K;
    std::cin >> N >> K;

    vint A(N);
    for (int i = 0; i < N; i++) {
      std::cin >> A[i];
    }
    std::sort(A.begin(), A.end());
    printf("Case #%d: %d\n", t + 1, solve(A, K, MASK, USED));
  }
  return 0;
}
