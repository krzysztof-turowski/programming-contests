#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using vdouble = std::vector<double>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

int war(const vdouble &A, const vdouble &B) {
  int index = 0, out = 0;
  REP(i, SIZE(A))   {
    while (B[index] < A[i] && index < SIZE(B)) {
      index++;
    }
    if (index - i > out) {
      out = index - i;
    }
  }
  return out;
}

int deceitful_war(vdouble &A, vdouble &B) {
  int index = 0;
  REP(i, SIZE(A) - index) {
    if (A[index + i] < B[i]) {
      index++, i--;
    }
  }
  return SIZE(A) - index;
}

int main() {
  int N;
  std::cin >> N;
  REP(t, N) {
    int T;
    std::cin >> T;
    vdouble A(T), B(T);
    REP(i, T) {
      std::cin >> A[i];
    }
    REP(i, T) {
      std::cin >> B[i];
    }
    std::sort(A.begin(), A.end()), std::sort(B.begin(), B.end());
    printf("Case #%d: %d %d\n", t + 1, deceitful_war(A, B), war(A, B));
  }
  return 0;
}
