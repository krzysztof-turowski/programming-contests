#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

const int MOD = 1000;
std::vector<int> M{6, -4, 1, 0}, A{6, 2};

std::vector<int> power(const std::vector<int> &M, const int &N) {
  if (N == 1) {
    return M;
  }
  std::vector<int> P = power(M, N / 2);
  std::vector<int> Q{
    (P[0] * P[0] + P[1] * P[2] + MOD) % MOD,
    (P[0] * P[1] + P[1] * P[3] + MOD) % MOD,
    (P[2] * P[0] + P[3] * P[2] + MOD) % MOD,
    (P[2] * P[1] + P[3] * P[3] + MOD) % MOD
  };
  if (N % 2) {
    std::vector<int> R{
      (Q[0] * M[0] + Q[1] * M[2] + MOD) % MOD,
      (Q[0] * M[1] + Q[1] * M[3] + MOD) % MOD,
      (Q[2] * M[0] + Q[3] * M[2] + MOD) % MOD,
      (Q[2] * M[1] + Q[3] * M[3] + MOD) % MOD
    };
    return R;
  }
  return Q;
}

std::vector<int> multiply(const std::vector<int> &M, std::vector<int> &A) {
  std::vector<int> Q{
    (M[0] * A[0] + M[1] * A[1] + MOD) % MOD,
    (M[2] * A[0] + M[3] * A[1] + MOD) % MOD
  };
  return Q;
}

int solve(const int &N) {
  return (multiply(power(M, N - 1), A)[0] + MOD - 1) % MOD;
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N;
    printf("Case #%d: %03d\n", t + 1, solve(N));
  }
  return 0;
}
