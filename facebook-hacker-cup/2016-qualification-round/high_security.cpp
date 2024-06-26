#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

using llong = int64_t;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

bool is_single(const std::string &A, const int &index) {
  bool left = (index == 0) || (A[index - 1] != '.');
  bool right = (index == A.length() - 1) || (A[index + 1] != '.');
  return left && A[index] == '.' && right;
}

void cover(std::string &A, std::string &B, const int &index) {
  A[index] = 'G';
  for (int i = index + 1; i < A.length() && A[i] == '.'; i++) {
    A[i] = 'C';
  }
  for (int i = index - 1; i >= 0 && A[i] == '.'; i--) {
    A[i] = 'C';
  }
  if (B[index] == '.') {
    B[index] = 'C';
  }
}

int find_next_empty(std::string &A, int index) {
  while (index < A.length() && A[index] != '.') {
    index++;
  }
  return index;
}

llong solve() {
  int N;
  std::string low, high;
  std::cin >> N, std::cin.ignore(2, '\n');
  std::cin >> low >> high;

  int out = 0;
  for (int index = 0; index < N;
      index = std::min(find_next_empty(low, index + 1), find_next_empty(high, index + 1))) {
    FOR(i, index, N - 1) {
      if (is_single(low, i)) {
        if (high[i] == '.') {
          cover(high, low, i), out++;
        } else {
          cover(low, high, i), out++;
        }
      } else if (is_single(high, i)) {
        if (low[i] == '.') {
          cover(low, high, i), out++;
        } else {
          cover(high, low, i), out++;
        }
      }
    }
    if (low[index] == '.') {
      cover(low, high, index), out++;
    } else if (high[index] == '.') {
      cover(high, low, index), out++;
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %lld\n", t + 1, solve());
  }
  return 0;
}
