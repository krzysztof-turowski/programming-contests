#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

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
    REP(i, D) REP(j, D) {
      room[i][j] = 0;
    }
    auto x = std::make_pair(0, D / 2), min = x, max = x;
    REP(i, path.size()) {
      if (path[i] == 'L') {
        dir = left(dir);
      } else if (path[i] == 'W') {
        room[x.first][x.second] |= dir;
        switch (dir) {
          case 1: x.first--; break;
          case 2: x.first++; break;
          case 4: x.second--; break;
          case 8: x.second++; break;
        }
        room[x.first][x.second] |= reverse(dir);

        if (x.first < min.first) {
          min.first = x.first;
        } else if (x.first > max.first) {
          max.first = x.first;
        }

        if (x.second < min.second) {
          min.second = x.second;
        } else if (x.second > max.second) {
          max.second = x.second;
        }
      } else if (path[i] == 'R') {
        dir = right(dir);
      } else if (path[i] == ' ') {
        entry = dir, dir = reverse(dir);
      }
    }

    min.first++;
    switch (entry) {
      case 2: max.first--; break;
      case 4: min.second++; break;
      case 8: max.second--; break;
    }

    printf("Case #%d:\n", t + 1);
    FOR(i, min.first, max.first) {
      FOR(j, min.second, max.second) {
        printf("%c", room[i][j] + (room[i][j] > 9 ? 'a' - 10 : '0'));
      }
      puts("");
    }
  }

  return 0;
}
