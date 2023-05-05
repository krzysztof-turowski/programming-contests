#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

#define MAX 10000

inline bool value(const int &a, const int &b) {
  return a > b;
}

double good(const int &N) {
  int p;
  double out = 0;
  std::vector<int> A(N);
  REP(i, MAX) {
    REP(k, N) {
      A[k] = k;
    }
    REP(k, N) {
      p = rand_r(NULL) % (N - k) + k, std::swap(A[k], A[p]);
    }
    REP(k, N) {
      out += value(A[k], k);
    }
  }
  return out / MAX;
}

double bad(const int &N) {
  int p;
  double out = 0;
  std::vector<int> A(N);

  REP(i, MAX) {
    REP(k, N) {
      A[k] = k;
    }
    REP(k, N) {
      p = rand_r(NULL) % N, std::swap(A[k], A[p]);
    }
    REP(k, N) {
      out += value(A[k], k);
    }
  }
  return out / MAX;
}

double score(const std::vector<int> &A) {
  double out = 0;
  REP(i, A.size()) {
    out += value(A[i], i);
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;
    std::vector<int> A(N);
    REP(i, N) {
      std::cin >> A[i];
    }
    double a = score(A), g = good(N), b = bad(N);
    printf("Case #%d: ", t + 1);
    if (fabs(a - g) < fabs(a - b)) {
      std::cout << "GOOD" << std::endl;
    } else {
      std::cout << "BAD" << std::endl;
    }
  }
  return 0;
}
