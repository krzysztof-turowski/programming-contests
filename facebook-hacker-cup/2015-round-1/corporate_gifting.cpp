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
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)

#define INF 1000000000

struct node {
  int minsum, rcolor, ncolor, delta;
  std::vector<int> child;
};

std::vector<node> T;

int recursion(const int &i) {
  if (T[i].child.size() == 0) {
    T[i].ncolor = 2;
    return T[i].minsum = T[i].rcolor = T[i].delta = 1;
  }

  int mintotal = 0;
  std::vector<int> coloradd(T[i].child.size() + 3);
  REP(j, coloradd.size()) {
    coloradd[j] = j;
  }
  FOREACH(child, T[i].child) {
    mintotal += recursion(*child), coloradd[T[*child].rcolor] += T[*child].delta;
  }
  int sum1 = INF, sum2 = INF, color1 = INF, color2 = INF;
  FOR(j, 1, coloradd.size() - 1) {
    int value = coloradd[j];
    if (value < sum1) {
      color2 = color1, sum2 = sum1, color1 = j, sum1 = value;
    } else if (value < sum2) {
      color2 = j, sum2 = value;
    }
  }
  T[i].rcolor = color1, T[i].delta = sum2 - sum1, T[i].ncolor = color2;
  return T[i].minsum = sum1 + mintotal;
}

int solve() {
  int N;
  std::cin >> N;
  T.clear(), T.resize(N);
  REP(i, N) {
    int a;
    std::cin >> a;
    if (a > 0) {
      T[a - 1].child.push_back(i);
    }
  }
  return recursion(0);
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    printf("Case #%d: %d\n", t + 1, solve());
  }
  return 0;
}
