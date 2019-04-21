#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int solve(const int &R, const int &C, const int &W) {
  return R * (C / W) + W - (C % W == 0);
}

int main() {
  int T, R, C, W;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> R >> C >> W;
    printf("Case #%d: %d\n", t + 1, solve(R, C, W));
  }
  return 0;
}
