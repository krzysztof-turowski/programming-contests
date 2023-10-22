#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <cassert>

using llong = int64_t;
using ldouble = long double;
using vint = std::vector<int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

bool solve(vint &X, const vint &A, const vint &B, const int &N) {
  vint all[N];
  REP(i, N) {
    bool first = false;
    FORD(j, i - 1, 0) {
      if (A[j] >= A[i]) {
        all[i].push_back(j);
      } else if (A[i] == A[j] + 1 && first == false) {
        all[j].push_back(i), first = true;
      }
    }
    first = false;
    FOR(j, i + 1, N - 1) {
      if (B[j] >= B[i]) {
        all[i].push_back(j);
      } else if (B[i] == B[j] + 1 && first == false) {
        all[j].push_back(i), first = true;
      }
    }
  }

  vint degree(N);
  REP(i, N) {
    for (auto it : all[i]) {
      degree[it]++;
    }
  }

  std::priority_queue<int, std::vector<int>, std::greater<int> > Q;
  REP(i, N) {
    if (degree[i] == 0) {
      Q.push(i);
    }
  }

  int count = 0;
  while (!Q.empty()) {
    int index = Q.top();
    Q.pop();

    X[index] = ++count;
    for (auto it : all[index]) {
      degree[it]--;
      if (degree[it] == 0) {
        Q.push(it);
      }
    }
  }
  return true;
}

int main() {
  int T, N;

  std::cin >> T;
  REP(t, T) {
    std::cin >> N;
    vint A(N), B(N), X(N);
    REP(i, N) {
      std::cin >> A[i];
    }
    REP(i, N) {
      std::cin >> B[i];
    }
    assert(solve(X, A, B, N));

    printf("Case #%d: ", t + 1);
    REP(i, N) {
      printf("%d ", X[i]);
    }
    puts("");
  }

  return 0;
}
