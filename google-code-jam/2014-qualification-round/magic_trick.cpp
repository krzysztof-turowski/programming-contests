#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using vint = std::vector<int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

void pick(vint &A) {
  int n, a;

  std::cin >> n;
  REP(i, 4 * (n - 1)) {
    std::cin >> a;
  }
  REP(i, 4) {
    std::cin >> A[i];
  }
  REP(i, 4 * (4 - n)) {
    std::cin >> a;
  }
  std::sort(A.begin(), A.end());
}

int main() {
  int N;
  std::cin >> N;
  REP(t, N) {
    vint A(4), B(4), C(4);
    pick(A), pick(B);

    int out = std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), C.begin()) - C.begin();
    if (out == 0) {
      printf("Case #%d: Volunteer cheated!\n", t + 1);
    } else if (out == 1) {
      printf("Case #%d: %d\n", t + 1, C[0]);
    } else {
      printf("Case #%d: Bad magician!\n", t + 1);
    }
  }

  return 0;
}
