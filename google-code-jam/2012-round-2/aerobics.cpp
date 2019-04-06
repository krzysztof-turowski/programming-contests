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
typedef std::vector<llong> vllong;
typedef std::vector<pint> vpint;
typedef std::vector<pdouble> vpdouble;

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
#define EPS 1e-5

struct point {
  int index;
  double x, y, r;
};

bool sort_by_index(const struct point &a, const struct point &b) {
  return a.index < b.index;
}

bool sort_by_radius(const struct point &a, const struct point &b) {
  return a.r > b.r;
}

double point_distance(const struct point &a, const struct point &b) {
  double x = a.x - b.x, y = a.y - b.y, r = a.r + b.r;
  return x * x + y * y - r * r;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N, W, L;
    std::cin >> N >> W >> L;

    std::vector<point> P(N);
    REP(i, N)
      P[i].index = i, std::cin >> P[i].r;
    std::sort(ALL(P), sort_by_radius);

    REP(i, N) {
      bool check;
      do {
        check = false;
        P[i].x = W * static_cast<double>(rand_r(NULL)) / RAND_MAX;
        P[i].y = L * static_cast<double>(rand_r(NULL)) / RAND_MAX;
        REP(j, i)
          if (point_distance(P[i], P[j]) < 0) {
            check = true;
            break;
          }
      } while (check);
    }

    std::sort(ALL(P), sort_by_index);
    printf("Case #%d: ", t + 1);
    FOREACH(it, P)
      printf("%.2lf %.2lf ", it->x, it->y);
    puts("");
  }

  return 0;
}
