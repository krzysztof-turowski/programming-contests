#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

const int MAX = 10000000;

std::vector<int> precompute_factors() {
  std::vector<int> out(MAX + 1);
  for (int i = 2; i <= MAX; i++) {
    if (out[i] > 0) {
      continue;
    }
    for (int j = i; j <= MAX; j += i) {
      out[j]++;
    }
  }
  return out;
}

int solve(const std::vector<int> &F, const int &a, const int &b, const int &n) {
  int count = 0;
  for (int i = a; i <= b; i++) {
    if (F[i] == n) {
      count++;
    }
  }
  return count;
}

int main() {
  int T, a, b, n;
  std::cin >> T;
  std::vector<int> F = precompute_factors();
  for (int t = 0; t < T; t++) {
    std::cin >> a >> b >> n;
    printf("Case #%d: %d\n", t + 1, solve(F, a, b, n));
  }
  return 0;
}
