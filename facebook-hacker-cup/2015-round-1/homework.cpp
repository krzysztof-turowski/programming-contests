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

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define MAX 10000001

bool primacity(int N) {
  int M = sqrt(N) + 1, K = 0;
  FOR(i, 2, M) {
    if (N % i == 0) {
      while (N % i == 0) {
        N /= i;
      }
      K++;
    }
    if (N == 1) {
      break;
    }
  }
  return K + (N > 1);
}

int solve(std::vector<int> &data) {
  int A, B, K;
  std::cin >> A >> B >> K;

  if (K >= 9) {
    return 0;
  }
  int out = 0;
  FOR(i, A, B) {
    if (data[i] == K) {
      out++;
    }
  }
  return out;
}

int main() {
  int T;
  std::vector<int> data(MAX), number(MAX);
  REP(i, MAX) {
    number[i] = i;
  }
  FOR(k, 2, sqrt(MAX) + 1) {
    if (data[k] == 0) {
      for (int i = k; i < MAX; i += k) {
        data[i]++;
        while (number[i] % k == 0) {
          number[i] /= k;
        }
      }
    }
  }
  REP(i, MAX) {
    if (number[i] > 1) {
      data[i]++;
    }
  }
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %d\n", t + 1, solve(data));
  }
  return 0;
}
