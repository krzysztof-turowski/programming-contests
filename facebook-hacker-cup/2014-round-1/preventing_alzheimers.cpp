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

int N_SMALL = 15, N_LARGE = 20, MAX_LARGE = 152;
std::vector<int> SMALL = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
std::vector<int> LARGE = {53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113,
                          127, 131, 137, 139, 149, 151};
int MAX = 1000000000;

int mask(const int &v) {
  int out = 0;
  for (int i = 0; i < N_SMALL; i++) {
    if (v % SMALL[i] == 0) {
      out |= (1 << i);
    }
  }
  return out;
}

int hit(const int &v) {
  int out = 0;
  for (int i = 0; i < N_LARGE; i++) {
    if (v % LARGE[i] == 0) {
      return i;
    }
  }
  return -1;
}

int solve(
    const std::vector<int> &A, const int &K, const std::vector<int> &MASK,
    const std::vector<int> &USED) {
  std::vector<int> V;
  int start = 0, zeros = 0, maximum = 0;
  for (int i = 0; i < A.size(); i++) {
    maximum = std::max(maximum, A[i]);
    if (A[i] > K) {
      V.push_back(A[i]);
    } else {
      start += K - A[i];
    }
    if (A[i] == 0) {
      zeros++;
    }
  }
  if (maximum <= K) {
    return start - (zeros > 0) * K;
  }
  std::vector<std::vector<std::vector<int>>> state(
      V.size() + 1,
      std::vector<std::vector<int>>(1 << N_SMALL, std::vector<int>(N_LARGE + 1, MAX)));
  state[0][0][0] = start;
  REP(i, V.size()) {
    REP(mask, 1 << N_SMALL) {
      FOR(j, 0, i + 1) {
        if (state[i][mask][j] == MAX) {
          continue;
        }
        for (int v = (V[i] + K - 1) / K; v <= LARGE[j]; v++) {
          if (mask & MASK[v]) {
            continue;
          }
          if (USED[v] >= 0 && USED[v] < j) {
            continue;
          }
          int m = mask | MASK[v], k = USED[v] >= 0 ? USED[v] + 1 : j;
          state[i + 1][m][k] = std::min(
              state[i + 1][m][k], state[i][mask][j] + v * K - V[i]);
        }
      }
    }
  }
  int out = MAX;
  REP(mask, 1 << N_SMALL) {
    FOR(i, 0, N_LARGE) {
      out = std::min(out, state[V.size()][mask][i]);
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  std::vector<int> MASK(MAX_LARGE), USED(MAX_LARGE);
  REP(i, MAX_LARGE) {
    MASK[i] = mask(i), USED[i] = hit(i);
  }
  REP(t, T) {
    int N, K;
    std::cin >> N >> K;
    std::vector<int> A(N);
    for (int i = 0; i < N; i++) {
      std::cin >> A[i];
    }
    std::sort(A.begin(), A.end());
    printf("Case #%d: %d\n", t + 1, solve(A, K, MASK, USED));
  }
  return 0;
}
