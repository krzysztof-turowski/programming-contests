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

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ST first
#define ND second
#define INF 1000000000LL
#define EPS 1e-5

typedef int POINTT;
typedef double POINTR;

struct POINT {
  POINTT x, y;

  explicit POINT(const POINTT x = 0, const POINTT y = 0) : x(x), y(y) { }

  bool operator ==(const POINT &A) {
    return A.x == x && A.y == y;
  }
};

bool is_zero(const POINTR &x) {
  return x >= -EPS && x <= EPS;
}

POINTR dot(POINT &A, POINT &B, POINT &C) {
  return (POINTR(B.x - A.x) * POINTR(C.x - A.x)) + (POINTR(B.y - A.y) * POINTR(C.y - A.y));
}

POINTR det(POINT &A, POINT &B, POINT &C) {
  return (POINTR(B.x - A.x) * POINTR(C.y - A.y)) - (POINTR(B.y - A.y) * POINTR(C.x - A.x));
}

POINTR length(POINT &A, POINT &B) {
  return sqrt(dot(A, B, B));
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    POINT a, b, c;
    std::cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

    POINTR P = det(a, b, c), A = length(a, b), B = length(b, c), C = length(c, a);
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
