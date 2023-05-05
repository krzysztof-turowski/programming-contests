#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <sstream>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

#define INF 1000000000

struct shop : std::pair<double, double>, std::vector<double> { };

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int P, S, gas;
    std::cin >> P >> S >> gas;

    std::string items[P];
    int perishable = 0;
    REP(i, P) {
      std::cin >> items[i];
      if (items[i][items[i].size() - 1] == '!') {
        items[i].resize(items[i].size() - 1), perishable |= (1 << i);
      }
    }

    struct shop shops[S + 1];
    std::string line, item;
    int value;
    REP(i, S) {
      shops[i].resize(P, INF);

      std::cin >> shops[i].first >> shops[i].second, std::getline(std::cin, line);
      REP(j, line.size()) {
        line[j] = line[j] != ':' ? line[j] : ' ';
      }
      std::stringstream stream(line);
      while (stream.good()) {
        stream >> item >> value;
        REP(j, P) {
          if (items[j] == item) {
            shops[i][j] = value;
            break;
          }
        }
      }
    }
    shops[S].first = shops[S].second = 0;

    double length[S + 1][S + 1];
    REP(i, S + 1) REP(j, S + 1) {
      double X = shops[i].first - shops[j].first, Y = shops[i].second - shops[j].second;
      length[i][j] = gas * sqrt(X * X + Y * Y);
    }

    double costN[1 << P][S], costP[1 << P][S];
    REP(i, 1 << P) REP(j, S) {
      costN[i][j] = costP[i][j] = INF;
    }
    REP(i, S) {
      costN[0][i] = costP[0][i] = length[S][i];
    }
    REP(i, 1 << P) REP(j, S) REP(k, P) {
      if (i & (1 << k)) {
        int h = i ^ (1 << k);

        if (perishable & (1 << k)) {
          REP(l, S) {
            costP[i][j] = std::min(costP[i][j], costN[h][l] + shops[j][k] + length[l][j]);
            costP[i][j] = std::min(
                costP[i][j], costP[h][l] + shops[j][k] + length[l][S] + length[S][j]);
          }
        } else {
          REP(l, S) {
            costN[i][j] = std::min(costN[i][j], costN[h][l] + shops[j][k] + length[l][j]);
            costN[i][j] = std::min(
                costN[i][j], costP[h][l] + shops[j][k] + length[l][S] + length[S][j]);
          }
        }
        costP[i][j] = std::min(costP[i][j], costP[h][j] + shops[j][k]);
      }
    }
    double E = INF;
    REP(i, S) {
      E = std::min(E, std::min(costN[(1 << P) - 1][i], costP[(1 << P) - 1][i]) + length[i][S]);
    }
    printf("Case #%d: %.7lf\n", t + 1, E);
  }

  return 0;
}
