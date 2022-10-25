#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

bool recurse(
    int v, std::vector<std::vector<int>> &G, std::map<int, int> &M,
    std::unordered_map<int, std::vector<int>> &preds, std::unordered_map<int, int> &pred) {
  auto it = preds.find(v);
  if (it != preds.end()) {
    auto L = it->second;
    preds.erase(it);
    for (auto u : L) {
      auto it_u = pred.find(u);
      if (it_u != pred.end()) {
        int pu = it_u->second;
        pred.erase(it_u);
        if (pu == -1 || recurse(pu, G, M, preds, pred)) {
          M[v] = u;
          return true;
        }
      }
    }
  }
  return false;
}

std::map<int, int> bipartite_matching(std::vector<std::vector<int>> &G, int N) {
  std::map<int, int> M;
  for (int u = 0; u < N; u++) {
    for (int v : G[u]) {
      if (!M.count(v)) {
        M[v] = u;
        break;
      }
    }
  }
  while (true) {
    std::set<int> inv_M;
    for (auto &[_, v] : M) {
      inv_M.insert(v);
    }
    std::unordered_map<int, int> pred;
    std::vector<int> layer;
    for (int u = 0; u < N; u++) {
      if (!inv_M.count(u)) {
        pred[u] = -1;
        layer.push_back(u);
      }
    }
    std::unordered_map<int, std::vector<int>> preds;
    std::vector<int> unmatched;
    while (layer.size() > 0 && unmatched.size() == 0) {
      std::unordered_map<int, std::vector<int>> next_layer;
      for (auto u : layer) {
        for (auto v : G[u]) {
          if (!preds.count(v)) {
            next_layer[v].push_back(u);
          }
        }
      }
      layer.clear();
      for (auto &[v, V] : next_layer) {
        preds[v] = V;
        if (M.count(v)) {
          layer.push_back(M[v]);
          pred[M[v]] = v;
        } else {
          unmatched.push_back(v);
        }
      }
    }
    if (unmatched.size() == 0) {
      break;
    }
    for (auto &v : unmatched) {
      recurse(v, G, M, preds, pred);
    }
  }
  return M;
}

int solve(const std::vector<std::pair<std::string, std::string>> &S) {
  std::map<std::string, int> V1, V2;
  int N1 = 0, N2 = 0;
  for (auto &[a, b] : S) {
    if (!V1.count(a)) {
      V1.insert(std::make_pair(a, N1++));
    }
    if (!V2.count(b)) {
      V2.insert(std::make_pair(b, N2++));
    }
  }
  std::vector<std::vector<int>> G(N1);
  for (auto &[a, b] : S) {
    G[V1[a]].push_back(V2[b]);
  }
  return S.size() - (N1 + N2 - bipartite_matching(G, N1).size());
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    std::cin >> N;
    std::cin.ignore(256, '\n');
    std::vector<std::pair<std::string, std::string>> S(N);
    for (int i = 0; i < N; i++) {
        std::cin >> S[i].first >> S[i].second;
    }
    printf("Case #%d: %d\n", t + 1, solve(S));
  }
  return 0;
}
