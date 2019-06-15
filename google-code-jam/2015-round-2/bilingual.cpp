#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

struct Edge {
  int v, flow, C, reverse_u;
};

class Graph {
 public:
  int N;
  std::vector<int> level;
  std::vector<std::vector<Edge>> A;

  explicit Graph(const int &size) : N(size) {
    A.resize(size), level.resize(size);
  }

  void add_edge(const int &u, const int &v, const int &C)  {
    Edge a{v, 0, C, static_cast<int>(A[v].size())}, b{u, 0, 0, static_cast<int>(A[u].size())};
    A[u].push_back(a), A[v].push_back(b);
  }
};

bool BFS(Graph &G, const int &s, const int &t) {
    for (auto &v : G.level) {
      v = -1;
    }
    G.level[s] = 0;

    std::queue<int> L;
    L.push(s);
    while (!L.empty()) {
      int u = L.front();
      L.pop();
      for (const auto &e : G.A[u]) {
        if (G.level[e.v] < 0 && e.flow < e.C) {
          G.level[e.v] = G.level[u] + 1, L.push(e.v);
        }
      }
    }
    return G.level[t] >= 0;
}

int push_flow(Graph &G, const int &u, const int &t, const int &flow, std::vector<int> &start) {
    if (u == t) {
      return flow;
    }
    for (int i = 0; i < G.A[u].size(); i++) {
      Edge &e = G.A[u][i];
      if (G.level[e.v] == G.level[u] + 1 && e.flow < e.C) {
        start[u] = i;
        int total_flow = push_flow(G, e.v, t, std::min(flow, e.C - e.flow), start);
        if (total_flow > 0) {
          e.flow += total_flow, G.A[e.v][e.reverse_u].flow -= total_flow;
          return total_flow;
        }
      }
    }
    return 0;
}

int max_flow(Graph &G, const int &s, const int &t, const int &MAX) {
  if (s == t) {
    return -1;
  }
  int out = 0;
  while (BFS(G, s, t)) {
    std::vector<int> start(G.N);
    int flow = push_flow(G, s, t, MAX, start);
    if (flow == 0) {
      break;
    }
    out += flow;
  }
  return out;
}

int solve(const std::vector<std::set<std::string>> &S) {
  std::set<std::string> W;
  for (const auto &s : S) {
    for (const auto &w : s) {
      W.insert(w);
    }
  }
  int MAX = W.size() + 1;
  std::map<std::string, int> V;
  Graph G(2 * W.size() + S.size());
  std::set<std::string>::iterator it = W.begin();
  for (int i = 0; i < W.size(); i++, ++it) {
    G.add_edge(2 * i, 2 * i + 1, 1), V[*it] = i;
  }
  for (int i = 0; i < S.size(); i++) {
    for (const auto &w : S[i]) {
      int index = V[w];
      G.add_edge(2 * W.size() + i, 2 * index, MAX);
      G.add_edge(2 * index + 1, 2 * W.size() + i, MAX);
    }
  }
  return max_flow(G, 2 * W.size(), 2 * W.size() + 1, MAX);
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::string W;
    std::cin >> N, std::cin.ignore(256, '\n');
    std::vector<std::set<std::string>> S(N);
    for (int i = 0; i < N; i++) {
      while (std::cin.peek() != '\r' && std::cin.peek() != '\n' && std::cin.peek() != -1) {
        std::cin >> W;
        S[i].insert(W);
      }
      std::cin.ignore(256, '\n');
    }
    printf("Case #%d: %d\n", t + 1, solve(S));
  }
  return 0;
}
