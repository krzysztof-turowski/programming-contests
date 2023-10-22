#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using llong = int64_t;

llong solve(const int &K, std::vector<int> &F) {
  std::sort(F.begin(), F.end(), std::greater<int>());
  llong out = 0;
  for (int i = 0; i < F.size(); i++) {
    out += (i / K + 1) * F[i];
  }
  return out;
}

int main() {
  int T, P, K, L;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> P >> K >> L;
    std::vector<int> F(L);
    for (int i = 0; i < L; i++) {
      std::cin >> F[i];
    }
    printf("Case #%d: %lld\n", t + 1, solve(K, F));
  }
  return 0;
}
