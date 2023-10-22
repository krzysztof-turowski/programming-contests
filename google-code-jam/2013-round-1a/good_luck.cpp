#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <map>

using llong = int64_t;
using ldouble = long double;
using vint = std::vector<int>;
using vllong = std::vector<llong>;
using vdouble = std::vector<double>;
using vstring = std::vector<std::string>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()
#define PART(c, k) c.begin(), c.begin() + (k)

#define ST first
#define ND second
#define INF 1000000000LL
#define INFL 1000000000000000000LL
#define MAX 20000

llong factorial(int n) {
  llong out = 1L;
  while (n) {
    out *= n, n--;
  }
  return out;
}

inline void generate_next_string(std::string &S, const int &N, const int &M) {
  int index = N - 1;
  while (index > 0 && S[index] == '0' + M) {
    index--;
  }
  S[index]++;
  FOR(i, index + 1, N - 1) {
    S[i] = S[index];
  }
}

void get_probabilities(
    vstring &name, vdouble &data, std::vector<std::map<llong, int>> &cond, vllong &F,
    const int &N, const int &M) {
  std::string S(N, '2');
  while (S[0] <= '0' + M) {
    vint U(M + 1, 0);
    REP(i, N) {
      U[S[i] - '0']++;
    }
    double p = static_cast<double>(F[N]);
    FOR(i, 2, M) {
      p /= F[U[i]];
    }
    REP(i, 1 << N) {
      llong v = 1;
      REP(j, N) {
        if (i & (1 << j)) {
          v *= (S[j] - '0');
        }
      }
      cond[SIZE(data)][v]++;
    }

    name.push_back(S);
    data.push_back(p);
    generate_next_string(S, N, M);
  }
}

int solve(vdouble data, const std::vector<std::map<llong, int>> &cond, vllong &V, const int &K) {
  int index = 0;
  REP(i, SIZE(data)) {
    auto &value = data[i];
    auto &condi = cond[i];
    REP(j, K) {
      auto it = condi.find(V[j]);
      if (it == condi.end()) {
        break;
      }
      value *= it->second;
    }
    if (data[index] < value) {
      index = i;
    }
  }

  return index;
}

int main() {
  int R, N, M, K;
  std::cin >> R >> N >> M >> K;

  vllong F(M + 1);
  REP(i, SIZE(F)) {
    F[i] = factorial(i);
  }
  vstring S;
  vdouble P;
  std::vector<std::map<llong, int>> C(MAX);
  vllong V(K);

  get_probabilities(S, P, C, F, N, M);

  printf("Case #1:\n");
  REP(t, R) {
    REP(i, K) {
      std::cin >> V[i];
    }
    std::cout << S[solve(P, C, V, K)] << std::endl;
  }
  return 0;
}
