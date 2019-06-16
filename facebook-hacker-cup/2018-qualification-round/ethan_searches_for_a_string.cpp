#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

bool compare_suffix(const std::string &A, int index) {
  for (int i = 0; i < A.size() - index; i++) {
    if (A[i] != A[i + index]) {
      return false;
    }
  }
  return true;
}

std::string solve(const std::string &A) {
  for (int i = 1; i < A.size(); i++) {
    if (A[0] == A[i] && !compare_suffix(A, i)) {
      return A.substr(0, i) + A;
    }
  }
  return "Impossible";
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::string A;
    std::cin >> A;
    printf("Case #%d: %s\n", t + 1, solve(A).c_str());
  }
  return 0;
}
