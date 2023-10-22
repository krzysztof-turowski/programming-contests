#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = uint64_t;
using ldouble = long double;
using vint = std::vector<int>;
using vstring = std::vector<std::string>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

const llong MOD = 1000000007ULL;

template <typename T>
void print(T tab) {
  REP(i, SIZE(tab)) {
    std::cout << tab[i] << " ";
  }
  std::cout << std::endl;
}

llong factorial(int index) {
  llong out = 1ULL;
  while (index > 1) {
    out = (out * static_cast<llong>(index)) % MOD, index--;
  }
  return out;
}

llong solve(vstring &S, int N) {
  // Remove duplicates
  REP(i, N) {
    int t = 1;
    FOR(j, 1, SIZE(S[i]) - 1)
      if (S[i][j] != S[i][j - 1])
        S[i][t++] = S[i][j];
    S[i].resize(t);
  }

  // Check interior
  vint X(26), Y(26);
  REP(i, N) {
    Y[S[i][0] - 'a']++, Y[S[i][SIZE(S[i]) - 1] - 'a']++;
    FOR(j, 1, SIZE(S[i]) - 2)
      X[S[i][j] - 'a']++;
  }
  REP(i, 26)
    if ((X[i] >= 1 && Y[i] >= 1) || X[i] >= 2)
      return 0;

  // Reduce to two-characters
  REP(i, N)
    if (SIZE(S[i]) >= 2) {
      if (S[i][0] != S[i][SIZE(S[i]) - 1]) {
        S[i][1] = S[i][SIZE(S[i]) - 1], S[i].resize(2);
      } else {
        return 0;
      }
    } else {
      S[i].resize(2), S[i][1] = S[i][0];
    }

  vint A(26, -1), B(26, -1), C(26);
  int count = 0;
  REP(i, N) {
    if (S[i][0] == S[i][1]) {
      C[S[i][0] - 'a']++;
    } else {
      A[S[i][0] - 'a'] = B[S[i][1] - 'a'] = i, count++;
    }
  }

  // Visiting
  vint visited(N);
  int group = 0;
  REP(i, 26) {
    if (A[i] >= 0 && B[i] < 0) {
      group++;
      int index = A[i];
      do {
        if (visited[index])
          return 0;
        count--, visited[index] = 1;
        index = A[S[index][1] - 'a'];
      } while (index >= 0);
    } else if (A[i] < 0 && B[i] < 0 && C[i] > 0) {
      group++;
    }
  }
  if (count > 0) {
    return 0;
  }

  llong out = factorial(group);
  REP(i, 26) {
    out = (out * factorial(C[i])) % MOD;
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;
    vstring S(N);
    REP(i, N) {
      std::cin >> S[i];
    }
    printf("Case #%d: ", t + 1);
    std::cout << solve(S, N) << std::endl;
  }

  return 0;
}
