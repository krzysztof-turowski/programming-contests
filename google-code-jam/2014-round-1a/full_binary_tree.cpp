#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using graph = std::vector<std::vector<int>>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

int subtree(const graph &G, const int &N, const int &index, const int &parent) {
  if (G[index].size() <= 1) {
    return 1;
  }
  if (G[index].size() == 2 && parent >= 0) {
    return 1;
  }
  std::vector<int> A;
  REP(i, G[index].size()) {
    if (G[index][i] != parent) {
      A.push_back(subtree(G, N, G[index][i], index));
    }
  }
  std::sort(A.begin(), A.end(), std::greater<int>());
  return A[0] + A[1] + 1;
}

int solve(const graph &G, const int &N) {
  int out = 0;
  REP(i, N) {
    out = std::max(out, subtree(G, N, i, -1));
    if (out == N) {
      return N;
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N, u, v;
    std::cin >> N;

    graph G(N);
    REP(i, N - 1) {
      std::cin >> u >> v, --u, --v, G[u].push_back(v), G[v].push_back(u);
    }
    printf("Case #%d: ", t + 1);
    std::cout << N - solve(G, N) << std::endl;
  }

  return 0;
}
