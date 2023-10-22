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
    REP(i, N) {
      P[i].index = i, std::cin >> P[i].r;
    }
    std::sort(P.begin(), P.end(), sort_by_radius);

    REP(i, N) {
      bool check;
      do {
        check = false;
        P[i].x = W * static_cast<double>(rand_r(NULL)) / RAND_MAX;
        P[i].y = L * static_cast<double>(rand_r(NULL)) / RAND_MAX;
        REP(j, i) {
          if (point_distance(P[i], P[j]) < 0) {
            check = true;
            break;
          }
        }
      } while (check);
    }

    std::sort(P.begin(), P.end(), sort_by_index);
    printf("Case #%d: ", t + 1);
    for (auto it : P) {
      printf("%.2lf %.2lf ", it.x, it.y);
    }
    puts("");
  }

  return 0;
}
