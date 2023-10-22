#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <queue>
#include <string>
#include <vector>

using pint = std::pair<int, int>;
using vint = std::vector<int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const int INF = 1000000000;

int row_length(const int &i, const int &S) {
  return (S + 1) / 2 + (i > S / 2 ? S - 1 - i : i);
}

int hex_distance(const pint &i, const pint &j) {
  int dx = j.first - i.first, dy = j.second - i.second;
  return dx * dy < 0 ? fabs(dx) + fabs(dy) : std::max(fabs(dx), fabs(dy));
}

vint Hungarian(const std::vector<vint> &G, const int &N) {
  vint match_x(N, -1), match_y(N, -1), index_x(N), index_y(N, 0), parent(N, -1);
  REP(i, N) {
    index_x[i] = *max_element(G[i].begin(), G[i].end());
  }
  REP(k, N) {
    std::vector<bool> used_x(N, false), used_y(N, false);
    vint slack(N, -1);
    std::queue<int> Q;
    REP(i, N) {
      if (match_x[i] == -1) {
        Q.push(i);
      }
    }
    int v = -1;
    while (v == -1) {
      while (!Q.empty()) {
        int i = Q.front();
        Q.pop(), used_x[i] = true;
        REP(j, N)
          if (!used_y[j] && (slack[j] == -1 || slack[j] > index_x[i] + index_y[j] - G[i][j])) {
            parent[j] = i, slack[j] = index_x[parent[j]] + index_y[j] - G[i][j];
            if (slack[j] == 0) {
              used_y[j] = true;
              if (match_y[j] != -1) {
                Q.push(match_y[j]);
              } else {
                v = j;
                goto finish;
              }
            }
          }
      }
      int x = -1;
      REP(i, N)
        if (!used_y[i] && (x == -1 || slack[i] < x)) {
          x = slack[i];
        }
      REP(i, N) {
        if (used_x[i]) {
          index_x[i] -= x;
        }
        if (used_y[i]) {
          index_y[i] += x;
        } else {
          slack[i] -= x;
          if (slack[i] == 0) {
            used_y[i] = true;
            if (match_y[i] != -1) {
              Q.push(match_y[i]);
            } else {
              v = i;
            }
          }
        }
      }
    }
    finish:
      while (v != -1) {
        int y = match_x[parent[v]];
        match_x[parent[v]] = v, match_y[v] = parent[v], v = y;
      }
  }
  return match_x;
}

int compute(const int &S, const std::vector<pint> &X, const std::vector<pint> &Y, const vint &C) {
  std::vector<vint> G(S);
  REP(i, S) {
    G[i].resize(S);
    REP(j, S)
      G[i][j] = -hex_distance(X[i], Y[j]) * C[i];
  }

  vint solution = Hungarian(G, S);

  int out = 0;
  REP(i, S)
    out += hex_distance(X[i], Y[solution[i]]) * C[i];
  return out;
}

int main() {
  int N;
  std::cin >> N;
  REP(t, N) {
    int value, S = 0;
    vint P, C;

    std::cin.ignore(1);
    while (std::cin.peek() != '\n') {
      std::cin >> value, S++, P.push_back(value);
    }
    REP(i, S) {
      std::cin >> value, C.push_back(value);
    }
    std::vector<pint> X, Y;
    REP(i, S) {
      int r = 0, c = 0;
      REP(j, S) {
        c += row_length(j, S);
        if (P[i] <= c) {
          if (r > S / 2) {
            c = P[i] + S - c - 1;
          } else {
            c = P[i] + row_length(j, S) - c - 1;
          }
          break;
        } else {
          r++;
        }
      }
      X.push_back(std::make_pair(r, c));
    }

    int out = INF;
    REP(i, S) {
      Y.push_back(std::make_pair(i, i));
    }
    out = std::min(out, compute(S, X, Y, C));
    Y.clear();

    REP(i, S) {
      Y.push_back(std::make_pair(i, (S - 1) / 2));
    }
    out = std::min(out, compute(S, X, Y, C));
    Y.clear();

    REP(i, S) {
      Y.push_back(std::make_pair((S - 1) / 2, i));
    }
    out = std::min(out, compute(S, X, Y, C));
    Y.clear();

    printf("Case #%d: %d\n", t + 1, out);
  }

  return 0;
}
