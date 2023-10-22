#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using llong = int64_t;

const llong MOD = 1000000007L;
const int L = 3;

llong solve(const std::vector<std::string> &G, const int &N) {
  std::vector<llong> out{1, 0, 0};
  for (int i = 0; i < N; i++) {
    if (G[1][i] != '#') {
      llong mid = out[1];
      out[1] = ((G[0][i] != '#' ? out[0] : 0) + (G[2][i] != '#' ? out[2] : 0)) % MOD;
      out[0] = (G[0][i] != '#' ? mid : 0), out[2] = (G[2][i] != '#' ? mid : 0);
    } else {
      return 0;
    }
  }
  return out[2];
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N, std::cin.ignore(256, '\n');
    std::vector<std::string> G(L);
    for (int i = 0; i < L; i++) {
      std::cin >> G[i];
    }
    printf("Case #%d: %lld\n", t + 1, solve(G, N));
  }
  return 0;
}
