#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

std::vector<std::pair<int, int>> get_values(
    const std::vector<std::priority_queue<int>> &Q, const std::vector<int> &R) {
  std::vector<std::pair<int, int>> out;
  for (int i = 0; i < R.size(); i++) {
    int low = Q[i].top() / (11 * R[i]) + (Q[i].top() % (11 * R[i]) != 0);
    int high = Q[i].top() / (9 * R[i]);
    out.push_back(std::make_pair(low, high));
  }
  return out;
}

bool has_empty(const std::vector<std::priority_queue<int>> &Q) {
  for (const auto q : Q) {
    if (q.empty()) {
      return true;
    }
  }
  return false;
}

bool has_intersection(const std::vector<std::pair<int, int>> &P) {
  std::pair<int, int> current = P[0];
  for (const auto &p : P) {
    current.first = std::max(current.first, p.first);
    current.second = std::min(current.second, p.second);
    if (current.first > current.second) {
      return false;
    }
  }
  return true;
}

int find_highest_low(const std::vector<std::pair<int, int>> &P) {
  int index = 0;
  for (int i = 1; i < P.size(); i++) {
    if (P[i].first > P[index].first) {
      index = i;
    }
  }
  return index;
}

int solve(const std::vector<int> &R, std::vector<std::priority_queue<int>> &Q) {
  int out = 0;
  while (!has_empty(Q)) {
    std::vector<std::pair<int, int>> P = get_values(Q, R);
    if (has_intersection(P)) {
      out++;
      for (int i = 0; i < Q.size(); i++) {
        Q[i].pop();
      }
    } else {
      int index = find_highest_low(P);
      Q[index].pop();
    }
  }
  return out;
}

int main() {
  int T, N, P;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> P;
    std::vector<int> R(N);
    for (int i = 0; i < N; i++) {
      std::cin >> R[i];
    }
    std::vector<std::priority_queue<int>> Q(N);
    for (int i = 0; i < N; i++) {
      for (int j = 0, q; j < P; j++) {
        std::cin >> q;
        Q[i].push(10 * q);
      }
    }
    printf("Case #%d: %d\n", t + 1, solve(R, Q));
  }
  return 0;
}
