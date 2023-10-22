#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using llong = int64_t;

const int MAX = 20, MOD = 1000000007, SIZE = 800001;

struct Node {
  std::list<Node*> neighbors;
  Node *parent = 0;
  int low = -1, high = -1;

  void add_edge(Node *v) {
    neighbors.push_back(v);
  }
};

std::vector<llong> F(SIZE);

void compute_F() {
  for (int i = 0; i < SIZE; i++) {
    F[i] = ((llong) i * (i - 1) / 2) % MOD;
  }
}

int set_low_high(Node *v) {
  std::queue<Node*> Q;
  std::list<Node*> L;
  Q.push(v);
  while (!Q.empty()) {
    Node *u = Q.front();
    Q.pop();
    L.push_front(u);
    for (auto w : u->neighbors) {
      if (w->parent == 0 && w != v) {
        w->parent = u;
        Q.push(w);
      }
    }
  }
  for (auto u : L) {
    u->low = 1;
    for (auto w : u->neighbors) {
      if (w->parent == u) {
        u->low += w->low;
      }
    }
  }
  for (auto u : L) {
    u->high = v->low - u->low;
  }
  return v->low;
}

int solve(std::list<std::tuple<int, int, int, int>> &E) {
  int N = E.size() + 1;
  std::vector<llong> S(N - 1, 0LL);
  for (int weight = 1; weight <= MAX; weight++) {
    std::vector<Node*> G(N);
    for (int i = 0; i < N; i++) {
      G[i] = new Node();
    }
    for (auto [u, v, w, _] : E) {
      if (w >= weight) {
        G[u]->add_edge(G[v]);
        G[v]->add_edge(G[u]);
      }
    }
    llong sum_binomial_2 = 0LL;
    for (int i = 0; i < N; i++) {
      if (G[i]->low != -1) {
        continue;
      }
      sum_binomial_2 = (sum_binomial_2 + F[set_low_high(G[i])]) % MOD;
    }
    for (auto [u, v, _, i] : E) {
      if (G[u]->parent == G[v]) {
        S[i] += F[G[u]->low] + F[G[u]->high] + MOD - F[G[u]->low + G[u]->high];
      } else if (G[v]->parent == G[u]) {
        S[i] += F[G[v]->low] + F[G[v]->high] + MOD - F[G[v]->low + G[v]->high];
      }
      S[i] = (S[i] + sum_binomial_2) % MOD;
    }
    for (int i = 0; i < N; i++) {
      delete G[i];
    }
  }
  llong out = 1;
  for (auto s : S) {
    out = (out * s) % MOD;
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  compute_F();
  for (int t = 0; t < T; t++) {
    int N, u, v, w;
    std::cin >> N;
    std::list<std::tuple<int, int, int, int>> E;
    for (int i = 0; i < N - 1; i++) {
      std::cin >> u >> v >> w;
      E.push_back(std::make_tuple(u - 1, v - 1, w, i));
    }
    printf("Case #%d: %d\n", t + 1, solve(E));
  }
  return 0;
}
