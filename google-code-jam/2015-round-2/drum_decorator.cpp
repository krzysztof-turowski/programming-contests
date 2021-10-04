#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

const llong MOD = 1000000007L;

llong S2(
    const int &rows, const int &C, const int &period,
    std::map<std::pair<int, int>, llong> &S);

llong S3(
    const int &rows, const int &C, const int &period,
    std::map<std::pair<int, int>, llong> &S) {
  if (rows == 0) {
    return 1;
  }
  if (rows == 1) {
    return 0;
  }
  return S2(rows - 2, C, period, S);
}

llong S2(
    const int &rows, const int &C, const int &period,
    std::map<std::pair<int, int>, llong> &S) {
  if (rows == 0) {
    return 1;
  }
  auto value = S.find(std::make_pair(rows, period));
  if (value != S.end()) {
    return value->second;
  }
  llong out = S3(rows - 1, C, period, S);
  if (rows >= 2) {
    if (C % 3 == 0) {
      if (period == 0) {
        out = (out + S3(rows - 2, C, 3, S)) % MOD;
      } else if (period == 4) {
        out = (out + S3(rows - 2, C, 12, S)) % MOD;
      } else {
        out = (out + 3L * S3(rows - 2, C, period, S)) % MOD;
      }
    }
    if (C % 6 == 0) {
      if (period == 0) {
        out = (out + S3(rows - 2, C, 6, S)) % MOD;
      } else if (period == 3) {
        out = (out + 3L * S3(rows - 2, C, 6, S)) % MOD;
      } else if (period == 4) {
        out = (out + 2L * S3(rows - 2, C, 12, S)) % MOD;
      } else {
        out = (out + 6L * S3(rows - 2, C, period, S)) % MOD;
      }
    }
  }
  if (rows >= 3) {
    if (C % 4 == 0) {
      if (period == 0) {
        out = (out + S3(rows - 3, C, 4, S)) % MOD;
      } else if (period == 3) {
        out = (out + S3(rows - 3, C, 12, S)) % MOD;
      } else if (period == 4) {
        out = (out + 4L * S3(rows - 3, C, 4, S)) % MOD;
      } else if (period == 6) {
        out = (out + 2L * S3(rows - 3, C, 12, S)) % MOD;
      } else {
        out = (out + 4L * S3(rows - 3, C, 12, S)) % MOD;
      }
    }
  }
  S[std::make_pair(rows, period)] = out % MOD;
  return out % MOD;
}

llong solve(const int &R, const int &C) {
  std::map<std::pair<int, int>, llong> S;
  return (S3(R, C, 0, S) + S2(R, C, 0, S)) % MOD;
}

int main() {
  int T, R, C;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> R >> C;
    printf("Case #%d: %lld\n", t + 1, solve(R, C));
  }
  return 0;
}
