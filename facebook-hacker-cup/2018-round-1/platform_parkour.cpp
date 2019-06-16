#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

const int INF = 1000001;

class parkourist {
 public:
  int A, B, U, D;
};

std::vector<int> get_heights(
    const int &N, const int &H1, const int &H2, const int &W,
    const int &X, const int &Y, const int &Z) {
  std::vector<int> out{H1, H2};
  llong A = H1, B = H2;
  for (int i = 3; i <= N; i++) {
    llong C = (W * A + X * B + Y) % Z;
    A = B, B = C, out.push_back(C);
  }
  return out;
}

bool check(
    const double &value, const std::vector<int> &H, const std::vector<int> &D,
    const std::vector<int> &U) {
  double low = H[0] - value, high = H[0] + value;
  for (int i = 0; i < H.size() - 1; i++) {
    low = std::max(H[i + 1] - value, low - D[i]);
    high = std::min(H[i + 1] + value, high + U[i]);
    if (low > high) {
      return false;
    }
  }
  return true;
}

double solve(
    const int &N, const int &M, const std::vector<int> &H, const std::vector<parkourist> &P) {
  std::vector<int> Dmin(N, INF), Umin(N, INF);
  for (const auto &p : P) {
    if (p.A < p.B) {
      for (int i = p.A - 1; i < p.B - 1; i++) {
        Dmin[i] = std::min(Dmin[i], p.D);
        Umin[i] = std::min(Umin[i], p.U);
      }
    } else {
      for (int i = p.B - 1; i < p.A - 1; i++) {
        Dmin[i] = std::min(Dmin[i], p.U);
        Umin[i] = std::min(Umin[i], p.D);
      }
    }
  }
  double low = 0, high = INF;
  while (high - low > 1e-7) {
    double mid = (low + high) / 2;
    if (check(mid, H, Dmin, Umin)) {
      high = mid;
    } else {
      low = mid;
    }
  }
  return high;
}

int main() {
  int T, N, M;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> M;
    int H1, H2, W, X, Y, Z;
    std::cin >> H1 >> H2 >> W >> X >> Y >> Z;
    std::vector<parkourist> P(M);
    for (int i = 0; i < M; i++) {
      std::cin >> P[i].A >> P[i].B >> P[i].U >> P[i].D;
    }
    printf("Case #%d: %.6lf\n", t + 1, solve(N, M, get_heights(N, H1, H2, W, X, Y, Z), P));
  }
  return 0;
}
