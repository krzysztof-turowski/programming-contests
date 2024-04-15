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

double EPS = 10e-7;

class point {
 public:
  double x, y, r;

  point() : x(0), y(0), r(0) { }
  point(double x, double y, double r) : x(x), y(y), r(r) { }
};

double distance(const point &P, const point &Q) {
  return std::sqrt((P.x - Q.x) * (P.x - Q.x) + (P.y - Q.y) * (P.y - Q.y));
}

bool check_cover(const point &C1, const point &C2, const std::vector<point> &P, double R) {
  for (auto p : P) {
    if (!(distance(p, C1) <= R - p.r + EPS) && !(distance(p, C2) <= R - p.r + EPS)) {
      return false;
    }
  }
  return true;
}

void get_centers(const point &A, const point &B, double R, std::vector<point> &out) {
  double d = distance(A, B), r1 = R - A.r, r2 = R - B.r;
  if (d > r1 + r2) {
    return;
  }
  double f = r1 / d;
  if (abs(d - r1 - r2) < EPS) {
    out.emplace_back(point(A.x + f * (B.x - A.x), A.y + f * (B.y - A.y), 0));
    return;
  }
  double angle = acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
  auto v = point(f * (B.x - A.x), f * (B.y - A.y), 0);
  out.emplace_back(point(
      A.x + v.x * cos(angle) - v.y * sin(angle), A.y + v.x * sin(angle) + v.y * cos(angle), 0));
  out.emplace_back(point(
      A.x + v.x * cos(angle) + v.y * sin(angle), A.y - v.x * sin(angle) + v.y * cos(angle), 0));
}

bool compute_cover(const std::vector<point> &P, double &R) {
  std::vector<point> S;
  for (auto p : P) {
    S.emplace_back(point(p.x, p.y, 0));
  }
  REP(i, P.size()) {
    FOR(j, i + 1, P.size() - 1) {
      get_centers(P[i], P[j], R, S);
    }
  }
  REP(i, S.size()) {
    FOR(j, i + 1, S.size() - 1) {
      if (check_cover(S[i], S[j], P, R)) {
        return true;
      }
    }
  }
  return false;
}

double solve(const std::vector<point> &P) {
  if (P.size() == 1) {
    return P[0].r;
  }
  double low = 1, high = 2000;
  while (low + EPS < high) {
    double mid = (low + high) / 2;
    if (compute_cover(P, mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  return high;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;
    std::vector<point> S(N);
    REP(i, N) {
      std::cin >> S[i].x >> S[i].y >> S[i].r;
    }
    printf("Case #%d: %lf\n", t + 1, solve(S));
  }
  return 0;
}
