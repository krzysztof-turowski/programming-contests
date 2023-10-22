#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using llong = int64_t;
using ldouble = long double;
using pint = std::pair<int, int>;
using vpint = std::vector<pint>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

int is_edge(const int &S, const pint &p) {
  if (p.first == 0 && p.second == 0)
    return 12;
  if (p.first == 0 && p.second == S - 1)
    return 11;
  if (p.first == S - 1 && p.second == 0)
    return 10;
  if (p.first == S - 1 && p.second == 2 * S - 2)
    return 9;
  if (p.first == 2 * S - 2 && p.second == S - 1)
    return 8;
  if (p.first == 2 * S - 2 && p.second == 2 * S - 2)
    return 7;
  if (p.first == 0)
    return 6;
  if (p.second - p.first == S - 1)
    return 5;
  if (p.second == 2 * S - 2)
    return 4;
  if (p.first == 2 * S - 2)
    return 3;
  if (p.first - p.second == S - 1)
    return 2;
  if (p.second == 0)
    return 1;
  return 0;
}

bool in_board(const int &S, const pint &p) {
  return std::min(p.first, p.second) >= 0 && std::max(p.first, p.second) <= 2 * S - 2
      && (p.first > p.second ? p.first - p.second : p.second - p.first) <= S - 1;
}

struct data {
  pint parent;
  int rank, mask;

  data(const pint &parent, const int &mask) : parent(parent), rank(0), mask(mask) { }
};

pint find(std::map<pint, data> &G, const pint &p) {
  pint &q = G.find(p)->second.parent;
  if (p.first == q.first && p.second == q.second)
    return p;
  return q = find(G, q);
}

bool join(std::map<pint, data> &G, const pint &p, const pint &q) {
  pint x = find(G, p), y = find(G, q);
  if (x.first == y.first && x.second == y.second)
    return true;

  data &dx = G.find(x)->second, &dy = G.find(y)->second;
  if (dx.rank > dy.rank) {
    dx.parent = dy.parent, dy.mask |= dx.mask;
  } else if (dx.rank < dy.rank) {
    dy.parent = dx.parent, dx.mask |= dy.mask;
  } else {
    dx.parent = dy.parent, dx.rank++, dy.mask |= dx.mask;
  }
  return false;
}

void solve(const int &S, vpint &moves) {
  std::string element = "";
  std::map<pint, data> G;

  const int L = 6, first[L] = { 1, 0, -1, -1, 0, 1 }, second[L] = { 1, 1, 0, -1, -1, 0 };

  REP(i, SIZE(moves)) {
    pint p(moves[i]);
    G.emplace(p, data(p, 1 << is_edge(S, p)));

    vpint C(L, pint{-1, -1});
    REP(j, L) {
      pint q(p.first + first[j], p.second + second[j]);
      if (G.find(q) != G.end()) {
        C[j] = find(G, q);
      }
    }
    REP(j, L) {
      pint q(p.first + first[j], p.second + second[j]);
      if (G.find(q) != G.end()) {
        join(G, p, q);
      }
    }

    data &dx = G.find(find(G, p))->second;
    int corners = 0, edges = 0;
    FOR(j, 1, 6) {
      if ((dx.mask >> j) & 1) {
        edges++;
      }
    }
    FOR(j, 7, 12) {
      if ((dx.mask >> j) & 1) {
        corners++;
      }
    }
    if (corners >= 2) {
      element += "bridge-";
    }
    if (edges >= 3) {
      element += "fork-";
    }
    REP(j, L) {
      if (in_board(S, C[j])) {
        int count = 0, empty = 0;
        FOR(k, j + 1, j + L)
          if (C[k % L] == C[j] && empty > 0) {
            count++, empty = 0;
          } else if (!in_board(S, C[k % L])) {
            empty++;
          }
        if (count >= 2) {
          element += "ring-";
          break;
        }
      }
    }
    if (!element.empty()) {
      std::cout << element.substr(0, element.length() - 1) << " in move " << i + 1 << std::endl;
      return;
    }
  }

  std::cout << "none" << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int S, M;
    std::cin >> S >> M;
    vpint moves(M);
    REP(i, M) {
      std::cin >> moves[i].first >> moves[i].second, moves[i].first--, moves[i].second--;
    }
    printf("Case #%d: ", t + 1);
    solve(S, moves);
  }

  return 0;
}
