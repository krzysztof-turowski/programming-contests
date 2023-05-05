#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

typedef std::vector<std::vector<int>> graph;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

struct data {
  std::string name;
  int index;

  explicit data(const std::string &name = "", const int &index = 0) : name(name), index(index) { }

  bool operator<(const data &a) const {
    return name < a.name;
  }
};

int reachable(const graph &G, const int &start, std::vector<bool> &used, const int &N) {
  std::vector<bool> V(N);
  std::queue<int> Q;
  Q.push(start);

  while (!Q.empty()) {
    int x = Q.front();
    Q.pop();
    if (V[x] || used[x]) {
      continue;
    }
    V[x] = true;
    REP(i, N) {
      if (G[x][i] == 1) {
        Q.push(i);
      }
    }
  }

  int count = 0;
  REP(i, V.size()) {
    count += (V[i] || used[i]);
  }
  return count;
}

std::string solve(graph &G, std::vector<data> &D, const int &N) {
  std::vector<bool> visited(N), used(N);
  std::vector<int> path;
  path.push_back(0), visited[0] = true;
  std::string out = D[path.back()].name;
  FOR(i, 1, N - 1) REP(j, N) {
    if (!visited[j]) {
      if (G[path.back()][j]) {
        G[path.back()][j] = 0;
        visited[j] = true, path.push_back(j);
        out += D[path.back()].name;
        break;
      }

      int index = -1;
      FORD(k, path.size() - 2, 0) {
        if (G[path[k]][j] == 1) {
          index = k;
          break;
        }
      }
      if (index >= 0) {
        FOR(k, index + 1, path.size() - 1) {
          G[path[k]][path[k - 1]] = 0, used[path[k]] = true;
        }
        G[path[index]][j] = 2;
        if (reachable(G, j, used, N) == N) {
          path.resize(index + 1), visited[j] = true, path.push_back(j);
          out += D[path.back()].name;
          break;
        }
        FOR(k, index + 1, path.size() - 1) {
          G[path[k]][path[k - 1]] = 1, used[path[k]] = false;
        }
        G[path[index]][j] = 1;
      }
    }
  }
  return out;
}

int main() {
  int T;

  std::cin >> T;
  REP(t, T) {
    int N, M, u, v;
    std::cin >> N >> M;
    graph G(N);
    std::vector<data> D(N);
    std::vector<int> reverse(N);

    REP(i, N) {
      std::cin >> D[i].name, D[i].index = i, G[i].resize(N);
    }
    std::sort(D.begin(), D.end());
    REP(i, N) {
      reverse[D[i].index] = i;
    }
    REP(i, M) {
      std::cin >> u >> v, --u, --v, G[reverse[u]][reverse[v]] = G[reverse[v]][reverse[u]] = 1;
    }
    printf("Case #%d: ", t + 1);
    std::cout << solve(G, D, N) << std::endl;
  }
  return 0;
}
