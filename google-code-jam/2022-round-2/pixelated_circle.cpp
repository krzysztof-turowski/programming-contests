#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

#define llong int64

const double HALF = 0.5;

llong count_perimeter(const int &R) {
  llong out = 1;
  for (llong r = 1; r <= R; r++) {
    llong x1 = r * cos(M_PI_4), y1 = floor(sqrt(r * r - x1 * x1) + HALF);
    llong x2 = x1 + 1, y2 = floor(sqrt(r * r - x2 * x2) + HALF);
    if (y2 >= x2) {
      x1 = x2, y1 = y2;
    }
    out += 4 * (2 * x1 + (x1 != y1));
  }
  return out;
}

llong count_circle(const int &R) {
  llong out = 0;
  for (llong x = -R; x <= R; x++) {
    out += 2 * floor(sqrt((R + HALF) * (R + HALF) - x * x)) + 1;
  }
  return out;
}

llong solve(int R) {
  return count_circle(R) - count_perimeter(R);
}

int main() {
  int T, R;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> R;
    printf("Case #%d: %lld\n", t + 1, solve(R));
  }
  return 0;
}
