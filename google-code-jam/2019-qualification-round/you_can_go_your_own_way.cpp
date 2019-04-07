#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::string solve(const std::string &L, const int &N) {
  std::string out(L.size(), 'X');
  for (std::size_t i = 0; i < L.size(); i++) {
    out[i] = L[i] == 'S' ? 'E' : 'S';
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    std::string L;
    std::cin >> N >> L;
    printf("Case #%d: %s\n", t + 1, solve(L, N).c_str());
  }
  return 0;
}
