#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

const int V[4][4] = { { 1, 2, 3, 4 }, { 2, -1, 4, -3 }, { 3, -4, -1, 2 }, { 4, 3, -2, -1 } };

int value(const int &X, const char &c) {
  int Y = c == 'i' ? 1 : (c == 'j' ? 2 : 3);
  return X > 0 ? V[X - 1][Y] : -V[-X - 1][Y];
}

bool solve(const std::string &W, const int &L) {
  int a = 2, q = 1;
  REP(i, SIZE(W)) {
    q = value(q, W[i]);
    if (a == q) {
      a++, q = 1;
    }
  }
  return a == 5 && q == 1;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int L;
    llong X;
    std::string word = "", W;
    std::cin >> L >> X >> W;
    if (X >= 12LL) {
      X = X % 4LL + 12LL;
    }
    REP(i, X) {
      word += W;
    }
    printf("Case #%d: %s\n", t + 1, solve(word, L) ? "YES" : "NO");
  }
  return 0;
}
