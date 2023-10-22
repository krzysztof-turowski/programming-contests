#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const double EPS = 1e-5;

struct Point {
  int x, y;

  explicit Point(const int x = 0, const int y = 0) : x(x), y(y) { }

  bool operator==(const Point &A) {
    return A.x == x && A.y == y;
  }
};

bool is_zero(const double &x) {
  return x >= -EPS && x <= EPS;
}

double dot(Point &A, Point &B, Point &C) {
  return (static_cast<double>(B.x - A.x) * static_cast<double>(C.x - A.x))
      + (static_cast<double>(B.y - A.y) * static_cast<double>(C.y - A.y));
}

double det(Point &A, Point &B, Point &C) {
  return (static_cast<double>(B.x - A.x) * static_cast<double>(C.y - A.y))
      - (static_cast<double>(B.y - A.y) * static_cast<double>(C.x - A.x));
}

double length(Point &A, Point &B) {
  return sqrt(dot(A, B, B));
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    Point a, b, c;
    std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

    double P = det(a, b, c), A = length(a, b), B = length(b, c), C = length(c, a);
    P = P > 0 ? P : -P;

    printf("Case #%d: ", t + 1);
    if (is_zero(P)) {
      puts("not a triangle");
    } else {
      if (is_zero(A - B) || is_zero(B - C) || is_zero(C - A)) {
        printf("isosceles ");
      } else {
        printf("scalene ");
      }
      if (is_zero(A * B - P) || is_zero(B * C - P) || is_zero(C * A - P)) {
        printf("right ");
      } else if (dot(a, b, c) > EPS && dot(b, c, a) > EPS && dot(c, a, b) > EPS) {
        printf("acute ");
      } else {
        printf("obtuse ");
      }
      puts("triangle");
    }
  }

  return 0;
}
