#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

const long double EPS = 10e-16;

long double get_intersection(
    const long double &x, const long double &y, const long double &a, const long double &r) {
  if (r * r <= x * x + y * y) {
    return 0;
  }
  if (r * r >= (x + a) * (x + a) + (y + a) * (y + a)) {
    return a * a;
  }
  if (a * a < EPS) {
    return 0;
  }
  return get_intersection(x, y, a / 2, r)
      + get_intersection(x + a / 2, y, a / 2, r)
      + get_intersection(x, y + a / 2, a / 2, r)
      + get_intersection(x + a / 2, y + a / 2, a / 2, r);
}

long double solve(
    const long double &f, const long double &R, const long double &t,
    const long double &r, const long double &g) {
  if (g <= 2 * f) {
    return 1;
  }
  long double out = 0;
  for (long double x = r + f; x < R - t - f; x += 2 * r + g) {
    for (long double y = r + f; y < R - t - f; y += 2 * r + g) {
      out += get_intersection(x / R, y / R, (g - 2 * f) / R, (R - t - f) / R);
    }
  }
  return 1.0 - 4 * out / M_PI;
}

int main() {
  int N;
  long double f, R, t, r, g;
  std::cin >> N;
  for (int n = 0; n < N; n++) {
    std::cin >> f >> R >> t >> r >> g;
    printf("Case #%d: %.6Lf\n", n + 1, solve(f, R, t, r, g));
  }
  return 0;
}
