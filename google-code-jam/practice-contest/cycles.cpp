#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

const int MOD = 9901;

int hamiltonian(
    const std::vector<std::deque<int>> &chains, const std::vector<int> &factorial, const int &n) {
  int paths = 0, length = 0;
  for (const auto &chain : chains) {
    if (chain.size() >= 2) {
      paths++, length += chain.size();
    }
  }
  if (paths == 0) {
    return (factorial[n - 1] / 2) % MOD;
  }
  return (((1 << (paths - 1)) % MOD) * factorial[n - length + paths - 1]) % MOD;
}

int solve(const int &n, const int &k, const std::vector<std::pair<int, int>> &F) {
  std::vector<int> factorial(n + 1, 1);
  for (int i = 1; i <= n; i++) {
    factorial[i] = (i * factorial[i - 1]) % MOD;
  }
  int out = 0;
  for (int i = 0; i < (1 << k); i++) {
    int count = 0;
    std::vector<std::deque<int>> chains;
    std::vector<int> index(n, -1);
    bool has_cycle = false;
    for (int j = 0; j < k; j++) {
      if (i & (1 << j)) {
        int u = F[j].first, v = F[j].second;
        if (index[v] == -1) {
          std::swap(u, v);
        }
        if (index[u] == -1 && index[v] == -1) {
          index[u] = index[v] = chains.size();
          chains.push_back(std::deque<int>{u, v});
        } else if (index[u] == index[v]) {
          auto &V = chains[index[v]];
          if (V.size() != n) {
            has_cycle = true;
            break;
          }
          if (*(V.begin()) != v && *(V.rbegin()) != v) {
            has_cycle = true;
            break;
          }
          if (*(V.begin()) != u && *(V.rbegin()) != u) {
            has_cycle = true;
            break;
          }
        } else if (index[u] == -1) {
          auto &V = chains[index[v]];
          if (*(V.rbegin()) == v) {
            std::reverse(std::begin(V), std::end(V));
          }
          if (*(V.begin()) == v) {
            V.push_front(u), index[u] = index[v];
          } else {
            has_cycle = true;
            break;
          }
        } else {
          auto &U = chains[index[u]];
          auto &V = chains[index[v]];
          if (*(U.begin()) == u) {
            std::reverse(std::begin(U), std::end(U));
          }
          if (*(V.rbegin()) == v) {
            std::reverse(std::begin(V), std::end(V));
          }
          if (*(V.begin()) == v && *(U.rbegin()) == u) {
            for (const auto &x : V) {
              U.push_back(x), index[x] = index[u];
            }
            V.clear();
          } else {
            has_cycle = true;
            break;
          }
        }
        count++;
      }
    }
    if (has_cycle) {
      continue;
    }
    int value = hamiltonian(chains, factorial, n);
    out = count % 2 ? (out - value + MOD) % MOD : (out + value) % MOD;
  }
  return out;
}

int main() {
  int T, n, k, u, v;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> n >> k;
    std::vector<std::pair<int, int>> F;
    for (int i = 0; i < k; i++) {
      std::cin >> u >> v;
      if (u > v) {
        std::swap(u, v);
      }
      F.push_back(std::make_pair(u - 1, v - 1));
      std::sort(F.begin(), F.end());
    }
    printf("Case #%d: %d\n", t + 1, solve(n, k, F));
  }
  return 0;
}
