#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()
#define PART(c, k) c.begin(), c.begin() + (k)

#define ST first
#define ND second
#define INF 1000000000LL
#define INFL 1000000000000000000LL
#define EPS 1e-6

#define DATA(i, j) P[(i) * M + (j)]

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
  int U[4] = {-1, 0, 0, 1};
  int V[4] = {0, -1, 1, 0};

  std::priority_queue<element> Q;
  Q.push(element(0, 0, 0.0));
  while (!Q.empty()) {
    int x = Q.top().x, y = Q.top().y;
    double time = Q.top().time;
    Q.pop();

    if (DATA(x, y).time != INF)
      continue;

    DATA(x, y).time = time;
    if (x == N - 1 && y == M - 1)
      break;

    REP(i, 4) {
      int xp = x + U[i], yp = y + V[i];
      if (xp >= 0 && xp < N && yp >= 0 && yp < M) {
        if (std::min(DATA(x, y).ceil, DATA(xp, yp).ceil)
            - std::max(DATA(x, y).floor, DATA(xp, yp).floor) < 50)
          continue;
        double timep = std::max(time, (50.0 + H - DATA(xp, yp).ceil) / 10);
        if (timep > 0)
          timep += (H - DATA(x, y).floor - timep * 10 >= 20 - EPS ? 1 : 10);
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
    REP(i, N) REP(j, M)
      std::cin >> DATA(i, j).ceil, DATA(i, j).time = INF;
    REP(i, N) REP(j, M)
      std::cin >> DATA(i, j).floor;

    solve(P, N, M, H);

    printf("Case #%d: %.1lf\n", t + 1, P.back().time);
  }

  return 0;
}
