#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define INF 1000000000

int LR[] = {-1, 1, 0, 0}, UD[] = {0, 0, -1, 1};

bool is_visible(const std::vector<std::string> &P, int p, int q, int a, int b, int dir) {
  if (dir == 0 && p == a && b > q) {
    FORD(i, b - 1, q) {
      if (P[p][i] != '.') {
        return false;
      }
    }
    return true;
  }
  if (dir == 1 && q == b && a > p) {
    FORD(i, a - 1, p) {
      if (P[i][q] != '.') {
        return false;
      }
    }
    return true;
  }
  if (dir == 2 && p == a && b < q) {
    FOR(i, b + 1, q) {
      if (P[p][i] != '.') {
        return false;
      }
    }
    return true;
  }
  if (dir == 3 && q == b && a < p) {
    FOR(i, a + 1, p) {
      if (P[i][q] != '.') {
        return false;
      }
    }
    return true;
  }
  return false;
}

bool is_available(
    const std::vector<std::string> &P, int p, int q, int move, std::map<char, int> &dir) {
  if (P[p][q] != '.') {
    return false;
  }
  REP(i, P.size()) {
    REP(j, P[i].size()) {
      if (P[i][j] == '<' || P[i][j] == '^' || P[i][j] == '>' || P[i][j] == 'v') {
        if (is_visible(P, p, q, i, j, (dir[P[i][j]] + move) % 4)) {
          return false;
        }
      }
    }
  }
  return true;
}

int solve(const std::vector<std::string> &P, int ps, int qs, int pg, int qg) {
  std::map<char, int> dir;
  dir['<'] = 0, dir['^'] = 1, dir['>'] = 2, dir['v'] = 3;

  std::vector<std::vector<std::vector<int>>> A(4);
  REP(k, 4) {
    A[k].resize(P.size());
    REP(i, P.size()) {
      A[k][i].resize(P[i].size());
      REP(j, P[i].size()) {
        A[k][i][j] = INF;
      }
    }
  }

  // Dijkstra
  std::queue<std::pair<int, std::pair<int, int>> > Q;
  Q.push(std::make_pair(0, std::make_pair(ps, qs)));
  while (!Q.empty()) {
    auto top = Q.front();
    int move = top.first, p = top.second.first, q = top.second.second;
    Q.pop();

    if (p == pg && q == qg) {
      return move;
    }
    if (A[move % 4][p][q] != INF) {
      continue;
    }
    A[move % 4][p][q] = move;

    if (p > 0 && is_available(P, p - 1, q, move + 1, dir)) {
      Q.push(std::make_pair(move + 1, std::make_pair(p - 1, q)));
    }
    if (q > 0 && is_available(P, p, q - 1, move + 1, dir)) {
      Q.push(std::make_pair(move + 1, std::make_pair(p, q - 1)));
    }
    if (p < P.size() - 1 && is_available(P, p + 1, q, move + 1, dir)) {
      Q.push(std::make_pair(move + 1, std::make_pair(p + 1, q)));
    }
    if (q < P[p].size() - 1 && is_available(P, p, q + 1, move + 1, dir)) {
      Q.push(std::make_pair(move + 1, std::make_pair(p, q + 1)));
    }
  }
  return 0;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int M, N;
    std::cin >> M >> N;

    std::vector<std::string> P(M);
    REP(i, M) {
      std::cin >> P[i];
    }
    int ps, qs, pg, qg;
    REP(i, M) {
      REP(j, P[i].size()) {
        if (P[i][j] == 'S') {
          ps = i, qs = j, P[i][j] = '.';
        } else if (P[i][j] == 'G') {
          pg = i, qg = j, P[i][j] = '.';
        }
      }
    }
    int value = solve(P, ps, qs, pg, qg);
    if (value > 0) {
      printf("Case #%d: %d\n", t + 1, value);
    } else {
      printf("Case #%d: impossible\n", t + 1);
    }
  }
  return 0;
}
