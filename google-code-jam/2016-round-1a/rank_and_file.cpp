#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
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

std::pair<int, int> find_min(
    const std::vector<std::vector<int>> &H, const int &index, const int &N,
    const std::set<int> &remaining) {
  std::pair<int, int> out(-1, -1);
  int min_value = INF;
  REP(i, 2 * N - 1) {
    if (!remaining.count(i)) {
      continue;
    }
    if (H[i][index] < min_value) {
      min_value = H[i][index], out.first = i, out.second = -1;
    } else if (H[i][index] == min_value) {
      out.second = i;
    }
  }
  return out;
}

std::vector<int> solve(const std::vector<std::vector<int>> &H, const int &N) {
  std::vector<std::vector<int>> R, C;
  int index = -1;
  std::set<int> remaining;
  for (int i = 0; i < 2 * N - 1; i++) {
    remaining.insert(i);
  }
  REP(i, N) {
    std::pair<int, int> indices = find_min(H, i, N, remaining);
    if (indices.second == -1) {
      C.push_back(H[indices.first]), R.push_back(vint(N)), index = i;
      remaining.erase(indices.first);
    } else {
      C.push_back(H[indices.first]), R.push_back(H[indices.second]);
      remaining.erase(indices.first), remaining.erase(indices.second);
    }
  }
  REP(i, N) {
    if (i == index) {
      R[index][i] = C[index][i];
    } else if (C[index][i] == C[i][index]) {
      R[index][i] = R[i][index];
    } else {
      R[index][i] = C[i][index];
    }
  }
  return R[index];
}

int main() {
  int T, N;
  std::cin >> T;
  REP(t, T) {
    std::cin >> N;
    std::vector<std::vector<int>> H(2 * N - 1);
    REP(i, 2 * N - 1) {
      H[i].resize(N);
      REP(j, N)
        std::cin >> H[i][j];
    }
    vint out = solve(H, N);
    printf("Case #%d:", t + 1);
    for (const auto &v : out) {
      printf(" %d", v);
    }
    printf("\n");
  }

  return 0;
}
