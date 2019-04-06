#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

#define ST first
#define ND second
#define INF 1000000000LL

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int A, B;
    std::cin >> A >> B;

    int temp = A, length = 0, size = 1;
    while (temp) {
      temp /= 10, length++, size *= 10;
    }
    size /= 10;

    bool table[B - A + 1];
    REP(i, B - A + 1)
      table[i] = 0;

    int score = 0;
    FOR(i, A, B) {
      if (table[i - A]) {
        continue;
      }
      int k = 0, C = i;
      FOR(j, 0, length) {
        if (C < A || C > B) {
          continue;
        } else if (!table[C - A]) {
          table[C - A] = 1, k++;
        }
        C = C / 10 + (C % 10) * size;
      }
      score += k * (k - 1) / 2;
    }

    printf("Case #%d: %d\n", t + 1, score);
  }

  return 0;
}
