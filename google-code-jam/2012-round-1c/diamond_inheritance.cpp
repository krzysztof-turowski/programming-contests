#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

using llong = int64_t;
using ldouble = long double;
using vint = std::vector<int>;
using graph = std::vector<vint>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

bool BFS(const graph &G, const int &N, const vint &start) {
  for (auto v : start) {
    vint visited(N);
    std::queue<int> Q;
    Q.push(v);
    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();

      visited[v]++;
      if (visited[v] > 1) {
        return true;
      }
      REP(i, SIZE(G[v])) {
        Q.push(G[v][i]);
      }
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
