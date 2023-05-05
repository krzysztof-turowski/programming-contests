#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

typedef int64_t llong;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

#define INF 1000000000LL

int solve(const std::vector<llong> &A, const std::vector<llong> &B, int N, int shift) {
  llong x = A[0] ^ B[shift];

  std::vector<llong> C(N);
  REP(i, N) {
    C[i] = B[i] ^ x;
  }
  sort(C.begin(), C.end());
  REP(i, N) {
    if (A[i] != C[i]) {
      return INF;
    }
  }
  int out = 0;
  while (x) {
    if (x % 2) {
      out++;
    }
    x >>= 1;
  }
  return out;
}

llong convert(const std::string &x) {
  llong out = 0ULL;
  REP(i, x.size()) {
    if (x[i] == '1') {
      out ^= (1ULL << i);
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N, L;
    std::cin >> N >> L;

    std::string x;
    std::vector<llong> A(N), B(N);
    REP(i, N) {
      std::cin >> x, A[i] = convert(x);
    }
    REP(i, N) {
      std::cin >> x, B[i] = convert(x);
    }
    std::sort(A.begin(), A.end());
    int out = INF;
    REP(i, N) {
      out = std::min(out, solve(A, B, N, i));
    }
    printf("Case #%d: ", t + 1);
    if (out <= L) {
      std::cout << out << std::endl;
    } else {
      std::cout <<  "NOT POSSIBLE" << std::endl;
    }
  }

  return 0;
}
