#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;
typedef std::vector<ldouble> vldouble;
typedef std::vector<std::string> vstring;
typedef std::vector<llong> vllong;
typedef std::vector<vint> graph;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ADD_EDGE(g, u, v) g[u].push_back(v), g[v].push_back(u)

#define ST first
#define ND second
#define INF 1000000000LL
#define EPS 1e-5

struct Point {
  double x, y;
  int index;
};

bool XYsort(const Point &a, const Point &b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

double cross(const Point &O, const Point &A, const Point &B) {
  return (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
}

void convex_hull(std::vector<Point> &P, std::vector<Point> &H) {
  int n = P.size(), k = 0;
  H.resize(2 * n);

  std::sort(ALL(P), XYsort);
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross(H[k - 2], H[k - 1], P[i]) < -1e-6) k--;
    H[k++] = P[i];
  }

  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t && cross(H[k - 2], H[k - 1], P[i]) < -1e-6) k--;
    H[k++] = P[i];
  }

  H.resize(k);
}

bool in_convex_hull(const std::vector<Point> &H, const Point &X) {
  REP(i, SIZE(H))
    if (H[i].index == X.index)
      return true;
  return false;
}

int bisection(const vdouble &D, const double &q, int low, int high) {
  while (low + 1 != high) {
    int mid = (low + high) / 2;
    if (D[mid % SIZE(D)] - q > M_PI + 1e-6) {
      high = mid;
    } else {
      low = mid;
    }
  }

  return low;
}

int solve(const std::vector<Point> &P, const Point &X) {
  vdouble D;
  REP(i, SIZE(P))
    if (P[i].index != X.index)
      D.push_back(atan2(P[i].y - X.y, P[i].x - X.x));
  std::sort(ALL(D));

  int out = INF;
  REP(i, SIZE(D)) {
    out = std::min(out, SIZE(P) - bisection(D, D[i], i, i + SIZE(D) - 1) - i + 2);
    D[i] += 2 * M_PI;
  }

  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;

    std::vector<Point> P(N), H;
    REP(i, N)
      std::cin >> P[i].x >> P[i].y, P[i].index = i;
    convex_hull(P, H);

    vint results(N);
    REP(i, N)
      results[P[i].index] = in_convex_hull(H, P[i]) ? 0 : solve(P, P[i]);

    printf("Case #%d:\n", t + 1);
    REP(i, N)
      std::cout << results[i] << std::endl;
  }

  return 0;
}
