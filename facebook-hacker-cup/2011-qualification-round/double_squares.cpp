#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

int solve(const llong &X) {
  const llong MAX_FIRST = sqrt(X / 2);
  int count = 0;
  for (int i = 0; i <= MAX_FIRST; i++) {
    llong y_sq = X - i * i, y = sqrt(y_sq);
    if (y * y == y_sq) {
      count++;
    }
  }
  return count;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    llong X;
    std::cin >> X;
    printf("Case #%d: %d\n", t + 1, solve(X));
  }
  return 0;
}
