#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

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

bool BFS(const graph &G, const int &N, const vint &start) {
  FOREACH(v, start) {
    vint visited(N);
    std::queue<int> Q;
    Q.push(*v);

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();

      visited[v]++;
      if (visited[v] > 1)
        return true;

      REP(i, SIZE(G[v]))
        Q.push(G[v][i]);
    }
  }

  return false;
}

int main() {
  int T;

  std::cin >> T;
  REP(t, T) {
    int N, M, v;
    std::cin >> N;

    graph G(N);
    vint start;

    REP(i, N) {
      std::cin >> M;
      REP(j, M)
        std::cin >> v, G[--v].push_back(i);
      if (M == 0)
        start.push_back(i);
    }

    printf("Case #%d: ", t + 1);
    if (BFS(G, N, start)) {
      std::cout << "Yes" << std::endl;
    } else {
      std::cout << "No" << std::endl;
    }
  }

  return 0;
}
