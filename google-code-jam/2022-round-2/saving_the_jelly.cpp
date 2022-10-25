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

double distance(const std::pair<double, double> &a, const std::pair<double, double> &b) {
  return pow(a.first - b.first, 2) + pow(a.second - b.second, 2);
}

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

std::vector<std::pair<int, int>> fix_matching(
    std::vector<std::vector<int>> &G, int N, std::map<int, int> &M) {
  std::vector<std::pair<int, int>> out;
  while (out.size() < N) {
    bool remove_cycle = true;
    for (int u = 0; u < N; u++) {
      if (G[u].size() == 0) {
        continue;
      }
      int j = G[u][G[u].size() - 1];
      if (M[j] == u) {
        out.push_back(std::make_pair(u + 1, j + 2));
        for (int v = 0; v < N; v++) {
          G[v].erase(std::remove(G[v].begin(), G[v].end(), j), G[v].end());
        }
        G[u].clear();
        M.erase(j);
        remove_cycle = false;
        break;
      }
    }
    if (remove_cycle) {
      std::vector<int> path, visited(N, 0);
      int v = std::find_if(G.begin(), G.end(), [](auto it){
        return it.size() > 0;
      }) - G.begin();
      while (!visited[v]) {
        path.push_back(v), visited[v] = true;
        v = M[G[v][G[v].size() - 1]];
      }
      path.push_back(v);
      int start = std::find(path.begin(), path.end(), v) - path.begin();
      for (int i = start; i < path.size(); i++) {
        M[G[path[i]][G[path[i]].size() - 1]] = path[i];
      }
    }
  }
  return out;
}

std::string solve(
    const std::vector<std::pair<double, double>> &C,
    const std::vector<std::pair<double, double>> &J, int N) {
  std::vector<double> R(N);
  for (int u = 0; u < N; u++) {
    R[u] = distance(C[u], J[0]);
  }
  std::vector<std::vector<int>> G(N);
  for (int u = 0; u < N; u++) {
    std::vector<std::pair<double, int>> Nu;
    for (int v = 0; v < N; v++) {
      double r = distance(C[u], J[v + 1]);
      if (r <= R[u]) {
        Nu.push_back(std::make_pair(-r, v));
      }
    }
    std::sort(Nu.begin(), Nu.end());
    for (auto &[r, v] : Nu) {
      G[u].push_back(v);
    }
  }
  auto M = bipartite_matching(G, N);
  if (M.size() < N) {
    return "IMPOSSIBLE";
  }
  std::stringstream s;
  s << "POSSIBLE";
  for (auto value : fix_matching(G, N, M)) {
    s << "\n" << value.first << " " << value.second;
  }
  return s.str();
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    std::cin >> N;
    std::vector<std::pair<double, double>> C(N), J(N + 1);
    for (int i = 0; i < N; i++) {
        std::cin >> C[i].first >> C[i].second;
    }
    for (int i = 0; i <= N; i++) {
        std::cin >> J[i].first >> J[i].second;
    }
    printf("Case #%d: %s\n", t + 1, solve(C, J, N).c_str());
  }
  return 0;
}
