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

std::string solve(const std::vector<llong> &F, const std::vector<llong> &G) {
  if (F.size() < G.size()) {
    return "no solution";
  }
  int DH = F.size() - G.size();
  std::vector<int> H;
  for (int i = 0; i <= DH; i++) {
    llong sum = F[i];
    for (int j = 1; j <= i; j++) {
      if (j >= G.size()) {
        break;
      }
      sum -= G[j] * H[i - j];
    }
    if (G[0] == 0 && F[0] == 0) {
      assert(0);
    } else if ((G[0] == 0 && F[0] != 0) || sum % G[0]) {
      return "no solution";
    } else {
      H.push_back(sum / G[0]);
    }
  }
  for (int i = DH + 1; i < F.size(); i++) {
    llong sum = F[i];
    for (int j = 0; j <= i; j++) {
      if (j >= G.size() || i - j >= H.size()) {
        continue;
      }
      sum -= G[j] * H[i - j];
    }
    if (sum != 0) {
      return "no solution";
    }
  }
  std::reverse(H.begin(), H.end());
  std::stringstream S;
  for (int i = 0; i < H.size() - 1; i++) {
    S << H[i] << " ";
  }
  S << H.back();
  return S.str();
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int DF, DG;
    std::cin >> DF;
    std::vector<llong> F(DF + 1);
    for (int i = 0; i <= DF; i++) {
      std::cin >> F[i];
    }
    std::cin >> DG;
    std::vector<llong> G(DG + 1);
    for (int i = 0; i <= DG; i++) {
      std::cin >> G[i];
    }
    std::reverse(F.begin(), F.end()), std::reverse(G.begin(), G.end());
    printf("Case #%d: %s\n", t + 1, solve(F, G).c_str());
  }
  return 0;
}
