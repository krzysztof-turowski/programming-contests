#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>

using llong = int64_t;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

#define INF 1000000000LL
#define MAX 101

void shorten(const std::string &s, std::pair<std::string, std::vector<int>> &d) {
  d.first = s.substr(0, 1), d.second.push_back(1);
  REP(i, s.size() - 1) {
    if (s[i] != s[i + 1]) {
      d.first += s.substr(i + 1, 1), d.second.push_back(1);
    } else {
      ++d.second.back();
    }
  }
}

llong solve(const std::vector<std::string> &S, const int &N) {
  std::vector<std::pair<std::string, std::vector<int>>> D(N);
  REP(i, N) {
    shorten(S[i], D[i]);
  }
  REP(i, N) FOR(j, i + 1, N - 1) {
    if (D[i].first != D[j].first) {
      return INF;
    }
  }
  llong out = 0;
  REP(i, D[0].second.size()) {
    llong low = INF;
    REP(j, MAX) {
      llong sum = 0;
      REP(k, N) {
        sum += std::max(D[k].second[i] - j, j - D[k].second[i]);
      }
      low = std::min(low, sum);
    }
    out += low;
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int N;
    std::cin >> N;
    std::vector<std::string> S(N);
    REP(i, N) {
      std::cin >> S[i];
    }
    int out = solve(S, N);
    if (out == INF) {
      printf("Case #%d: Fegla Won\n", t + 1);
    } else {
      printf("Case #%d: %d\n", t + 1, out);
    }
  }
  return 0;
}
