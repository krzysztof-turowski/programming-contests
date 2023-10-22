#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using llong = int64_t;
using ldouble = long double;
using vllong = std::vector<llong>;
using pint = std::pair<int, int>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()
#define PART(c, k) c.begin(), c.begin() + (k)

struct three {
  vllong data;
  llong sum;

  three(const llong &X, const llong &Y, const llong &Z) : sum(X + Y + Z) {
    data.push_back(X), data.push_back(Y), data.push_back(Z);
  }
};

void generate_threes(const vllong &S, std::vector<three> &T, const int &N) {
  REP(i, N) {
    FOR(j, i + 1, N - 1) {
      FOR(k, j + 1, N - 1) {
        T.push_back(three(S[i], S[j], S[k]));
      }
    }
  }
}

bool solve(const vllong &S, vllong &A, vllong &B, vllong &C, const int &N) {
  std::vector<three> T;
  generate_threes(S, T, N);

  std::map<llong, pint> D;
  REP(i, SIZE(T)) {
    FOR(j, i + 1, SIZE(T) - 1) {
      llong diff = T[i].sum >= T[j].sum ? T[i].sum - T[j].sum : T[j].sum - T[i].sum;
      std::pair<std::map<llong, pint>::iterator, bool> it =
          D.insert(std::make_pair(diff, std::make_pair(i, j)));
      if (it.second == false) {
        int a = i, b = j, c = it.first->second.first, d = it.first->second.second;
        if (T[a].sum + T[c].sum != T[b].sum + T[d].sum) {
          std::swap(c, d);
        }
        copy(ALL(T[a].data), A.begin());
        copy(ALL(T[c].data), A.begin() + 3);
        copy(ALL(T[b].data), B.begin());
        copy(ALL(T[d].data), B.begin() + 3);

        vllong C(6);
        sort(ALL(A)), sort(ALL(B));
        c = std::set_intersection(ALL(A), ALL(B), C.begin()) - C.begin();
        a = std::set_difference(ALL(A), PART(C, c), A.begin()) - A.begin();
        b = std::set_difference(ALL(B), PART(C, c), B.begin()) - B.begin();
        if (a == 0) {
          continue;
        }
        a = std::unique(PART(A, a)) - A.begin();
        b = std::unique(PART(B, b)) - B.begin();
        llong sum = 0;
        REP(i, a) {
          sum += A[i];
        }
        REP(i, b) {
          sum -= B[i];
        }
        if (sum != 0) {
          continue;
        }
        A.resize(a), B.resize(b);
        return true;
      }
    }
  }
  return false;
}

int main() {
  int T, N;

  std::cin >> T;
  REP(t, T) {
    std::cin >> N;

    vllong S(N), A(6), B(6), C(6);
    REP(i, N)
      std::cin >> S[i];
    std::sort(ALL(S));

    printf("Case #%d:\n", t + 1);
    if (solve(S, A, B, C, std::min(N, 50))) {
      REP(i, SIZE(A))
        printf("%lld ", A[i]);
      puts("");
      REP(i, SIZE(B))
        printf("%lld ", B[i]);
      puts("");
    } else {
      puts("Impossible");
    }
  }

  return 0;
}
