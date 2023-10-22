#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

using llong = int64_t;
using ldouble = long double;
using pldouble = std::pair<ldouble, ldouble>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

const ldouble EPS = 1e-5;

struct cold_compare {
  bool operator() (pldouble &A, pldouble &B) {
    return A.second < B.second;
  }
};

struct hot_compare {
  bool operator() (pldouble &A, pldouble &B) {
    return A.second > B.second;
  }
};

bool mix(pldouble &A, pldouble &B, const ldouble &X) {
  if (A.first * A.second + B.first * B.second > (A.first + B.first) * X) {
    ldouble R = (B.first * X - B.first * B.second) / (A.second - X);
    B.first += R, A.first -= R, B.second = X;
    return false;
  }

  ldouble R = (A.first * X - A.first * A.second) / (B.second - X);
  A.first += R, B.first -= R, A.second = X;
  return true;
}

ldouble solve() {
  int N;
  ldouble V, X;
  std::cin >> N >> V >> X;

  ldouble R, C, Rout = 0;
  std::priority_queue<pldouble, std::vector<pldouble>, cold_compare> cold;
  std::priority_queue<pldouble, std::vector<pldouble>, hot_compare> hot;
  REP(i, N) {
    std::cin >> R >> C;
    if (fabs(C - X) < EPS) {
      Rout += R;
    } else if (C < X) {
      cold.push(std::make_pair(R, C));
    } else {
      hot.push(std::make_pair(R, C));
    }
  }

  while (!hot.empty() && !cold.empty()) {
    pldouble P = hot.top(), Q = cold.top();
    hot.pop(), cold.pop();

    if (mix(P, Q, X)) {
      Rout += P.first, cold.push(Q);
    } else {
      Rout += Q.first, hot.push(P);
    }
  }

  return Rout == 0 ? -1 : V / Rout;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: ", t + 1);
    ldouble out = solve();
    out >= 0 ? printf("%.8Lf\n", out) : puts("IMPOSSIBLE");
  }

  return 0;
}
