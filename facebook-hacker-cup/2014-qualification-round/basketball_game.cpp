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
#define SIZE(x) static_cast<int>(x.size())
#define ALL(c) c.begin(), c.end()

struct player {
  std::string name;
  int shots, height, draft, time;

  player() {
    std::cin >> name >> shots >> height, time = 0;
  }

  bool operator<(const player &b) const {
    return shots > b.shots || (shots == b.shots && height > b.height);
  }
};

bool leaving(const player &a, const player &b) {
  return a.time > b.time || (a.time == b.time && a.draft > b.draft);
}

void solve() {
  int N, M, P;
  std::cin >> N >> M >> P;

  std::vector<player> X;
  REP(i, N) {
    X.push_back(player());
  }
  std::sort(ALL(X));
  REP(i, N) {
    X[i].draft = i;
  }

  std::vector<player> team[2], bench[2];
  REP(i, 2 * P) {
    team[i % 2].push_back(X[i]);
  }
  FOR(i, 2 * P, N - 1) {
    bench[i % 2].push_back(X[i]);
  }
  REP(i, M) REP(k, 2) {
    REP(j, P) {
      team[k][j].time++;
    }
    if (SIZE(bench[k]) > 0) {
      int a = min_element(ALL(team[k]), leaving) - team[k].begin();
      int b = max_element(ALL(bench[k]), leaving) - bench[k].begin();
      std::swap(team[k][a], bench[k][b]);
    }
  }

  std::vector<std::string> Y;
  REP(k, 2) REP(i, P) {
    Y.push_back(team[k][i].name);
  }
  std::sort(ALL(Y));
  REP(i, SIZE(Y) - 1) {
    std::cout << Y[i] << " ";
  }
  std::cout << Y.back() << std::endl;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: ", t + 1), solve();
  }
  return 0;
}
