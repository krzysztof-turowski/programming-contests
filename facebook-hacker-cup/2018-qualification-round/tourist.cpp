#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using llong = int64_t;

std::string solve(
    const std::vector<std::string> &A, const llong &N, const llong &K, const llong &V) {
  std::stringstream out;
  llong start = (K * (V - 1)) % N, finish = (K * V - 1) % N;
  if (start <= finish) {
    for (int i = start; i <= finish; i++) {
      out << A[i] << " ";
    }
  } else {
    for (int i = 0; i <= finish; i++) {
      out << A[i] << " ";
    }
    for (int i = start; i < N; i++) {
      out << A[i] << " ";
    }
  }
  out.unget();
  return out.str();
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    llong N, K, V;
    std::cin >> N >> K >> V;
    std::vector<std::string> A(N);
    for (int i = 0; i < N; i++) {
      std::cin >> A[i];
    }
    printf("Case #%d: %s\n", t + 1, solve(A, N, K, V).c_str());
  }
  return 0;
}
