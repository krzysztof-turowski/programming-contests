#ifdef _MSC_VER
  #define _CRT_SECURE_NO_WARNINGS
#endif

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <sstream>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::pair<ldouble, ldouble> pldouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;
typedef std::vector<ldouble> vldouble;
typedef std::vector<std::string> vstring;
typedef std::vector<llong> vllong;
typedef std::vector<vint> graph;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ADD_EDGE(g, u, v) g[u].push_back(v), g[v].push_back(u)

#define ST first
#define ND second
#define INF 1000000000LL
#define EPS 1e-5

struct shop : pdouble, vdouble { };

int main {
  int T;
  cin >> T;
  REP(t, T) {
    int P, S, gas;
    std::cin >> P >> S >> gas;

    std::string items[P];
    int perishable = 0;
    REP(i, P) {
      std::cin >> items[i];
      if (items[i][SIZE(items[i]) - 1] == '!') {
        items[i].resize(SIZE(items[i]) - 1), perishable |= (1 << i);
      }
    }

    struct shop shops[S + 1];
    std::string line, item;
    int value;
    REP(i, S) {
      shops[i].resize(P, INF);

      std::cin >> shops[i].ST >> shops[i].ND, getline(cin, line);
      REP(j, SIZE(line))
        line[j] = line[j] != ':' ? line[j] : ' ';

      std::stringstream stream(line);
      while (stream.good()) {
        stream >> item >> value;
        REP(j, P)
          if (items[j] == item) {
            shops[i][j] = value;
            break;
          }
      }
    }
    shops[S].ST = shops[S].ND = 0;

    double length[S + 1][S + 1];
    REP(i, S + 1) REP(j, S + 1) {
      double X = shops[i].ST - shops[j].ST, Y = shops[i].ND - shops[j].ND;
      length[i][j] = gas * sqrt(X * X + Y * Y);
    }

    double costN[1 << P][S], costP[1 << P][S];
    REP(i, 1 << P) REP(j, S)
      costN[i][j] = costP[i][j] = INF;
    REP(i, S)
      costN[0][i] = costP[0][i] = length[S][i];

    REP(i, 1 << P) REP(j, S) REP(k, P)
    if (i & (1 << k)) {
      int h = i ^ (1 << k);

      if (perishable & (1 << k)) {
        REP(l, S) {
          costP[i][j] = min(costP[i][j], costN[h][l] + shops[j][k] + length[l][j]);
          costP[i][j] = min(costP[i][j], costP[h][l] + shops[j][k] + length[l][S] + length[S][j]);
        }
      } else {
        REP(l, S) {
          costN[i][j] = min(costN[i][j], costN[h][l] + shops[j][k] + length[l][j]);
          costN[i][j] = min(costN[i][j], costP[h][l] + shops[j][k] + length[l][S] + length[S][j]);
        }
      }
      costP[i][j] = min(costP[i][j], costP[h][j] + shops[j][k]);
    }

    double E = INF;
    REP(i, S)
      E = std::min(E, std::min(costN[(1 << P) - 1][i], costP[(1 << P) - 1][i]) + length[i][S]);

    printf("Case #%d: %.7lf\n", t + 1, E);
  }

  return 0;
}
