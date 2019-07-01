#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

const llong MOD = 1000000007LL;

llong solve(std::string &S, const int &K) {
  std::vector<llong> P(S.size());
  P[0] = 2;
  for (int i = 1; i < P.size(); i++) {
    P[i] = (2 * P[i - 1]) % MOD;
  }
  llong out = 0;
  for (int i = S.size() - 1, balance = 0; i >= 0; i--) {
    if (S[i] == 'B') {
      balance++;
    } else {
      balance--;
    }
    if (balance > K) {
      S[i] = 'A', out = (out + P[i]) % MOD, balance -= 2;
    }
    if (balance <= 0) {
      balance = 0;
    }
  }
  return out;
}

int main() {
  int T, N, K;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> K, std::cin.ignore(256, '\n');
    std::string S;
    std::cin >> S;
    printf("Case #%d: %lld\n", t + 1, solve(S, K));
  }
  return 0;
}
