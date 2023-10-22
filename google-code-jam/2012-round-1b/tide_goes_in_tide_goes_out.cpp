#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const int INF = 1000000000;
const double EPS = 1e-5;
const int U[4] = {-1, 0, 0, 1}, V[4] = {0, -1, 1, 0};

constexpr auto& DATA(auto &P, int M, int i, int j) {
  return P[(i) * M + (j)];
}

struct data {
  double floor, ceil, time;
};

struct element {
  int x, y;
  double time;

  element(const int &x, const int &y, const double &time) : x(x), y(y), time(time) { }

  bool operator<(const element &a) const {
      return time > a.time;
  }
};

void solve(std::vector<data> &P, int N, int M, int H) {
  std::priority_queue<element> Q;
  Q.emplace(0, 0, 0.0);
  while (!Q.empty()) {
    auto [x, y, time] = Q.top();
    Q.pop();
    if (DATA(P, M, x, y).time != INF) {
      continue;
    }
    DATA(P, M, x, y).time = time;
    if (x == N - 1 && y == M - 1) {
      break;
    }
    REP(i, 4) {
      int xp = x + U[i], yp = y + V[i];
      if (xp >= 0 && xp < N && yp >= 0 && yp < M) {
        if (std::min(DATA(P, M, x, y).ceil, DATA(P, M, xp, yp).ceil)
            - std::max(DATA(P, M, x, y).floor, DATA(P, M, xp, yp).floor) < 50) {
          continue;
        }
        double timep = std::max(time, (50.0 + H - DATA(P, M, xp, yp).ceil) / 10);
        if (timep > 0) {
          timep += (H - DATA(P, M, x, y).floor - timep * 10 >= 20 - EPS ? 1 : 10);
        }
        Q.push(element(xp, yp, timep));
      }
    }
  }
}

int main() {
  int T, H, N, M;

  std::cin >> T;
  REP(t, T) {
    std::cin >> H >> N >> M;
    std::vector<data> P(N * M);
    REP(i, N) REP(j, M) {
      std::cin >> DATA(P, M, i, j).ceil, DATA(P, M, i, j).time = INF;
    }
    REP(i, N) REP(j, M) {
      std::cin >> DATA(P, M, i, j).floor;
    }
    solve(P, N, M, H);
    printf("Case #%d: %.1lf\n", t + 1, P.back().time);
  }

  return 0;
}
