#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <queue>
#include <set>
#include <string>
#include <vector>

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
#define INF 1000000000LL
#define EPS 1e-5

int get_longest_path(
    const int &v, std::vector<std::set<int>> &G, const std::vector<int> &B) {
  int out = 1;
  for (const auto &u : G[v]) {
    if (u == B[v]) {
      continue;
    }
    out = std::max(out, 1 + get_longest_path(u, G, B));
  }
  return out;
}

int solve(const std::vector<int> &B, const int &N) {
  int first = 0;
  REP(i, N) {
    std::vector<bool> visited(N, false);
    int v = B[i];
    int count = 1;
    while (true) {
      if (v == i) {
        first = std::max(first, count);
        break;
      }
      if (visited[v]) {
        break;
      }
      count++, visited[v] = true, v = B[v];
    }
  }

  int second = 0;
  std::vector<std::set<int>> reverse(N);
  REP(i, N) {
    reverse[B[i]].insert(i);
  }
  REP(i, N) {
    if (i < B[i] && B[B[i]] == i) {
      second += get_longest_path(i, reverse, B) + get_longest_path(B[i], reverse, B);
    }
  }
  return std::max(first, second);
}

int main() {
  int T, N, v;
  std::cin >> T;
  REP(t, T) {
    std::cin >> N;
    std::vector<int> B(N);
    REP(i, N) {
      std::cin >> v, B[i] = v - 1;
    }
    printf("Case #%d: %d\n", t + 1, solve(B, N));
  }

  return 0;
}
