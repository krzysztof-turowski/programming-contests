#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::tuple<std::string, std::string> solve(const std::string &S) {
  std::string A(S.size(), '0'), B(S.size(), '0');
  for (std::size_t i = 0; i < S.size(); i++) {
    int v = S[i] - '0';
    if (v == 4) {
      A[i] += 1, B[i] += 3;
    } else {
      B[i] += v;
    }
  }
  int index = A.find_first_not_of('0');
  return std::make_tuple(A.substr(index), B);
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::string S;
    std::cin >> S;
    auto [A, B] = solve(S);
    printf("Case #%d: %s %s\n", t + 1, A.c_str(), B.c_str());
  }
  return 0;
}
