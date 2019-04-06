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
#define INF 1000000000

char left(const char &d) {
  return d > 2 ? 8 / d : 4 * d;
}

char right(const char &d) {
  return d > 2 ? d / 4 : 8 / d;
}

char reverse(const char &d) {
  return d > 2 ? 32 / d : 2 / d;
}

int main() {
  const int D = 1000;

  int T;
  std::cin >> T, std::cin.ignore(256, '\n');
  REP(t, T) {
    std::string path;
    std::getline(std::cin, path);

    char room[D][D], dir = 2, entry;
    REP(i, D) REP(j, D)
      room[i][j] = 0;

    pint x = std::make_pair(0, D / 2), min = x, max = x;

    REP(i, SIZE(path)) {
      if (path[i] == 'L') {
        dir = left(dir);
      } else if (path[i] == 'W') {
        room[x.ST][x.ND] |= dir;
        switch (dir) {
          case 1: x.ST--; break;
          case 2: x.ST++; break;
          case 4: x.ND--; break;
          case 8: x.ND++; break;
        }
        room[x.ST][x.ND] |= reverse(dir);

        if (x.ST < min.ST) {
          min.ST = x.ST;
        } else if (x.ST > max.ST) {
          max.ST = x.ST;
        }

        if (x.ND < min.ND) {
          min.ND = x.ND;
        } else if (x.ND > max.ND) {
          max.ND = x.ND;
        }
      } else if (path[i] == 'R') {
        dir = right(dir);
      } else if (path[i] == ' ') {
        entry = dir, dir = reverse(dir);
      }
    }

    min.ST++;
    switch (entry) {
      case 2: max.ST--; break;
      case 4: min.ND++; break;
      case 8: max.ND--; break;
    }

    printf("Case #%d:\n", t + 1);
    FOR(i, min.ST, max.ST) {
      FOR(j, min.ND, max.ND)
        printf("%c", room[i][j] + (room[i][j] > 9 ? 'a' - 10 : '0'));
      puts("");
    }
  }

  return 0;
}
