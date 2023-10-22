#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

void mirror(int &p, int &s) {
  s = -s, p += s;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int H, W, D;
    std::cin >> H >> W >> D;

    std::string map[H];
    int x0, y0;
    for (int j = 0; j < H; j++) {
      std::getline(std::cin, map[j]);
      size_t found = map[j].find('X');
      if (found != std::string::npos)
        x0 = j, y0 = static_cast<int>(found);
    }

    int score = 0;
    FOR(s, -D, D)
    for (int k = sqrt(static_cast<double>(D) * D - s * s), t = -k; t <= k; t++) {
      if (s == 0 && t == 0)
        continue;

      int x = x0, y = y0, sx = s > 0 ? 1 : -1, sy = t > 0 ? 1 : -1;
      int dx = 2 * (s > 0 ? s : -s), dy = 2 * (t > 0 ? t : -t), error;
      if (dx >= dy) {
        int error_t = error = dx / 2;
        for (int u = 0; u < dx / 2; u++, error_t = error) {
          x += sx, error += dy;
          if (error > dx) {
            y += sy, error -= dx;
            if (error + error_t > dx) {
              if (map[x - sx][y] == '#') {
                mirror(y, sy);
                if (map[x][y] == '#')
                  mirror(x, sx);
              } else if (map[x][y] == '#') {
                mirror(x, sx);
              }
            } else if (error + error_t < dx) {
              if (map[x][y - sy] == '#') {
                mirror(x, sx);
                if (map[x][y] == '#')
                  mirror(y, sy);
              } else if (map[x][y] == '#') {
                mirror(y, sy);
              }
            } else if (error + error_t == dx && map[x][y] == '#') {
              if (map[x - sx][y] != '#' && map[x][y - sy] != '#') {
                break;
              } else if (map[x - sx][y] == '#' && map[x][y - sy] == '#') {
                mirror(x, sx), mirror(y, sy), error = dx - error_t;
              } else if (map[x - sx][y] == '#') {
                mirror(y, sy);
              } else if (map[x][y - sy] == '#') {
                mirror(x, sx);
              }
            }
          } else if (map[x][y] == '#') {
            mirror(x, sx);
          }

          if (x == x0 && y == y0 && error == dx / 2) {
            if (u == dx / 2 - 1)
              score++;
            break;
          }
        }
      } else {
        int error_t = error = dy / 2;
        for (int u = 0; u < dy / 2; u++, error_t = error) {
          y += sy, error += dx;
          if (error > dy) {
            x += sx, error -= dy;
            if (error + error_t > dy) {
              if (map[x][y - sy] == '#') {
                mirror(x, sx);
                if (map[x][y] == '#')
                  mirror(y, sy);
              } else if (map[x][y] == '#') {
                mirror(y, sy);
              }
            } else if (error + error_t < dy) {
              if (map[x - sx][y] == '#') {
                mirror(y, sy);
                if (map[x][y] == '#')
                  mirror(x, sx);
              } else if (map[x][y] == '#') {
                mirror(x, sx);
              }
            } else if (error + error_t == dy && map[x][y] == '#') {
              if (map[x - sx][y] != '#' && map[x][y - sy] != '#') {
                break;
              } else if (map[x - sx][y] == '#' && map[x][y - sy] == '#') {
                mirror(x, sx), mirror(y, sy), error = dy - error_t;
              } else if (map[x][y - sy] == '#') {
                mirror(x, sx);
              } else if (map[x - sx][y] == '#') {
                mirror(y, sy);
              }
            }
          } else if (map[x][y] == '#') {
            mirror(y, sy);
          }

          if (x == x0 && y == y0 && error == dy / 2) {
            if (u == dy / 2 - 1) {
              score++;
            }
            break;
          }
        }
      }
    }

    printf("Case #%d: %d\n", t + 1, score);
  }

  return 0;
}
