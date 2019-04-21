#include <algorithm>
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::stringstream recurse(const int &X, const int &Y, const int &K) {
  std::stringstream out;
  if (K == 1) {
    if (X == 1) {
      out << 'E';
    } else if (X == -1) {
      out << 'W';
    } else if (Y == 1) {
      out << 'N';
    } else {
      out << 'S';
    }
    return out;
  }
  if (fabs(X) >= fabs(Y)) {
    if (X >= 0) {
      out = recurse(X - K, Y, K - 1);
      out << 'E';
    } else {
      out = recurse(X + K, Y, K - 1);
      out << 'W';
    }
  } else {
    if (Y >= 0) {
      out = recurse(X, Y - K, K - 1);
      out << 'N';
    } else {
      out = recurse(X, Y + K, K - 1);
      out << 'S';
    }
  }
  return out;
}

std::string solve(const int &X, const int &Y) {
  int S = fabs(X) + fabs(Y);
  int K = 0;
  while ((K * (K + 1) / 2) < S || (K * (K + 1) / 2) % 2 != S % 2) {
    K++;
  }
  return recurse(X, Y, K).str();
}

void check(const std::string &W, const int &X, const int &Y) {
  int x = 0, y = 0;
  for (int i = 0; i < W.size(); i++) {
    if (W[i] == 'N') {
      y += (i + 1);
    } else if (W[i] == 'S') {
      y -= (i + 1);
    } else if (W[i] == 'E') {
      x += (i + 1);
    } else {
      x -= (i + 1);
    }
  }
  assert(X == x);
  assert(Y == y);
}

int main() {
  int T, X, Y;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> X >> Y;
    std::string out = solve(X, Y);
    printf("Case #%d: %s\n", t + 1, out.c_str());
    check(out, X, Y);
  }
  return 0;
}
