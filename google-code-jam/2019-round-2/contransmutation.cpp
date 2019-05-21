#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>

typedef int64_t llong;

const llong MOD = 1000000007L;

std::vector<std::set<int>> reverse(const std::vector<std::set<int>> &R) {
  std::vector<std::set<int>> out(R.size());
  for (int i = 0; i < R.size(); i++) {
    for (const auto &v : R[i]) {
      out[v].insert(i);
    }
  }
  return out;
}

void fill_order(
    const std::vector<std::set<int>> &R, const int &v,
    std::vector<bool> &visited, std::stack<int> &S) {
  if (visited[v]) {
    return;
  }
  visited[v] = true;
  for (const auto &u : R[v]) {
    if (!visited[u]) {
      fill_order(R, u, visited, S);
    }
  }
  S.push(v);
}

std::map<int, int> SCC(
    const std::vector<std::set<int>> &R, const std::vector<std::set<int>> &R_rev) {
  std::stack<int> S;
  std::vector<bool> visited(R.size(), false);
  for (int i = 0; i < R.size(); i++) {
    fill_order(R, i, visited, S);
  }

  std::map<int, int> out;
  std::vector<bool> processed(R.size(), false);
  std::queue<int> Q;
  int index = 0;
  while (!S.empty()) {
    int v = S.top();
    S.pop();
    if (!processed[v]) {
      Q.push(v);
      while (!Q.empty()) {
        int u = Q.front();
        Q.pop(), processed[u] = true, out.insert(std::make_pair(u, index));
        for (const auto &w : R_rev[u]) {
          if (!processed[w]) {
            Q.push(w);
          }
        }
      }
      index++;
    }
  }
  return out;
}

void visit(
    const std::vector<std::set<int>> &R, const int &v,
    std::vector<int> &visited, std::vector<int> &out) {
  if (visited[v] > 0) {
    return;
  }
  visited[v] = 1;
  for (const auto &u : R[v]) {
    visit(R, u, visited, out);
  }
  visited[v] = 2, out.push_back(v);
}

std::vector<int> topological_sort(const std::vector<std::set<int>> &R) {
  std::vector<int> A(R.size(), 0), out;
  visit(R, 0, A, out);
  return out;
}

std::string solve(
    const std::vector<std::set<int>> &R, const std::vector<llong> &G) {
  std::vector<std::set<int>> R_rev = reverse(R);
  std::map<int, int> S = SCC(R, R_rev);
  std::vector<int> T = topological_sort(R_rev);
  std::stable_sort(T.begin(), T.end(), [&](const int &a, const int &b) -> bool {
      return S.find(a)->second < S.find(b)->second;
  });
  assert(T.back() == 0);

  std::set<int> U;
  for (int i = 0; i < T.size(); i++) {
    U.insert(T[i]);
  }

  std::vector<llong> out(G);
  std::vector<bool> test(G.size());
  for (int i = 0; i < G.size(); i++) {
    test[i] = (out[i] != 0);
  }
  for (int t = 0; t < 2; t++) {
    for (int i = 0; i < T.size(); i++) {
      int u = *(R[T[i]].begin()), v = *(R[T[i]].rbegin());
      test[u] = test[u] || test[T[i]], test[v] = test[v] || test[T[i]];
    }
  }
  for (int i = 0; i < T.size(); i++) {
    int u = *(R[T[i]].begin()), v = *(R[T[i]].rbegin());
    if (!test[u] || !test[v]) {
      continue;
    }
    if ((S[T[i]] == S[u] && U.count(v)) || (S[T[i]] == S[v] && U.count(u))) {
      return "UNBOUNDED";
    }
  }
  for (int i = 0; i < T.size() - 1; i++) {
    int u = *(R[T[i]].begin()), v = *(R[T[i]].rbegin());
    out[u] = (out[T[i]] + out[u]) % MOD, out[v] = (out[T[i]] + out[v]) % MOD, out[T[i]] = 0;
  }
  return std::to_string(out[T.back()]);
}

int main() {
  int T, M, a, b;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> M;
    std::vector<std::set<int>> R(M);
    std::vector<llong> G(M);
    for (int i = 0; i < M; i++) {
      std::cin >> a >> b;
      R[i].insert(a - 1), R[i].insert(b - 1);
    }
    for (int i = 0; i < M; i++) {
      std::cin >> G[i];
    }
    printf("Case #%d: %s\n", t + 1, solve(R, G).c_str());
  }
}
