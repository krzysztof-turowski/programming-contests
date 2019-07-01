#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

char solve(const std::string &S) {
  int B = 0;
  for (int i = 1; i < S.size(); i++) {
    if (S[i] == 'B') {
      B++;
    }
  }
  if (B == 0 || B == S.size() - 1) {
    return 'N';
  }
  return 2 * B >= S.size() - 1 ? 'Y' : 'N';
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::string A;
    std::cin >> A;
    printf("Case #%d: %c\n", t + 1, solve(A));
  }
  return 0;
}
