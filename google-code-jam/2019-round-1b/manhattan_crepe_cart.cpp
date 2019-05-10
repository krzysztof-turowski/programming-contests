#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

class person {
 public:
  int X, Y;
  char dir;
};

std::pair<int, int> solve(const std::vector<person> &V, const int &Q) {
  int X = 0, Y = 0, best_X = 0, best_Y = 0;
  for (int i = 0; i <= Q; i++) {
    int sum_X = 0, sum_Y = 0;
    for (const auto &p : V) {
      if ((p.dir == 'N' && i > p.Y) || (p.dir == 'S' && i < p.Y)) {
        sum_Y++;
      }
      if ((p.dir == 'E' && i > p.X) || (p.dir == 'W' && i < p.X)) {
        sum_X++;
      }
    }
    if (sum_X > best_X) {
      X = i, best_X = sum_X;
    }
    if (sum_Y > best_Y) {
      Y = i, best_Y = sum_Y;
    }
  }
  return std::make_pair(X, Y);
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int P, Q;
    std::cin >> P >> Q;
    std::vector<person> V(P);
    for (int i = 0; i < P; i++) {
      std::cin >> V[i].X >> V[i].Y >> V[i].dir;
    }
    auto point = solve(V, Q);
    printf("Case #%d: %d %d\n", t + 1, point.first, point.second);
  }
  return 0;
}
