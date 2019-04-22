#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const int MAX = 400;

void add_keys(std::vector<int> &keys, const int &type, const std::vector<int> &contains) {
  --keys[type];
  for (const auto &key : contains) {
    ++keys[key];
  }
}

void remove_keys(std::vector<int> &keys, const int &type, const std::vector<int> &contains) {
  ++keys[type];
  for (const auto &key : contains) {
    --keys[key];
  }
}

void dfs(
    const int &v, const std::vector<int> &type, const std::vector<std::vector<int>> &contains,
    const std::vector<bool> &visited, std::vector<bool> &reachable) {
  reachable[v] = true;
  for (int u = 0; u < visited.size(); u++) {
    for (const auto &key : contains[v]) {
      if (visited[u] || reachable[u]) {
        continue;
      }
      if (type[u] == key) {
        dfs(u, type, contains, visited, reachable);
      }
    }
  }
}

bool is_possible(
    const std::vector<int> &keys, const std::vector<int> &type,
    const std::vector<std::vector<int>> &contains, const std::vector<bool> &visited) {
  std::vector<int> all_keys(keys);
  for (int v = 0; v < visited.size(); v++) {
    if (visited[v]) {
      continue;
    }
    for (const auto &key : contains[v]) {
      ++all_keys[key];
    }
  }
  for (int v = 0; v < visited.size(); v++) {
    if (visited[v]) {
      continue;
    }
    if (all_keys[type[v]] == 0) {
      return false;
    }
    --all_keys[type[v]];
  }
  std::vector<bool> reachable(visited.size(), false);
  for (int v = 0; v < visited.size(); v++) {
    if (!visited[v] && !reachable[v] && keys[type[v]] > 0) {
      dfs(v, type, contains, visited, reachable);
    }
  }
  for (int v = 0; v < visited.size(); v++) {
    if (!visited[v] && !reachable[v]) {
      return false;
    }
  }
  return true;
}

std::string solve(
    std::vector<int> &keys, const std::vector<int> &type,
    const std::vector<std::vector<int>> &contains) {
  int N = type.size(), vertex;
  std::vector<bool> visited(N, false);
  if (!is_possible(keys, type, contains, visited)) {
    return "IMPOSSIBLE";
  }
  std::stringstream out;
  for (int i = 0; i < N; i++) {
    for (int v = 0; v < N; v++) {
      if (visited[v] || keys[type[v]] == 0) {
        continue;
      }
      visited[v] = true, add_keys(keys, type[v], contains[v]);
      bool possible = is_possible(keys, type, contains, visited);
      if (possible) {
        vertex = v;
        break;
      }
      visited[v] = false, remove_keys(keys, type[v], contains[v]);
    }
    out << vertex + 1 << " ";
  }
  return out.str();
}

int main() {
  int T, K, N, k, v;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> K >> N;
    std::vector<int> type(N), keys(MAX);
    for (int i = 0; i < K; i++) {
      std::cin >> v, ++keys[v - 1];
    }
    std::vector<std::vector<int>> contains(N);
    for (int i = 0; i < N; i++) {
      std::cin >> v >> k, type[i] = v - 1;
      for (int j = 0; j < k; j++) {
        std::cin >> v, contains[i].push_back(v - 1);
      }
    }
    std::string out = solve(keys, type, contains);
    printf("Case #%d: %s\n", t + 1, out.c_str());
  }
  return 0;
}
