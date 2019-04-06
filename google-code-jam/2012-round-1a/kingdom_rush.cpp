#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

typedef int64_t llong;
typedef long double ldouble;
typedef std::pair<int, int> pint;
typedef std::pair<double, double> pdouble;
typedef std::vector<int> vint;
typedef std::vector<double> vdouble;

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

struct level {
  int value, priority, level;
};

struct compare {
  inline bool operator() (const struct level &a, const struct level &b) {
    return a.value < b.value;
  }
};

struct promote {
  inline bool operator() (const struct level &a, const struct level &b) {
    return a.priority < b.priority;
  }
};

int main() {
  int T;
  std::cin >> T;
  REP(t, T) {
    int L;
    std::cin >> L;

    int completed[L];
    std::deque<level> first, second;
    std::priority_queue<level, std::deque<level>, promote> third;
    first.resize(L), second.resize(L);

    REP(i, L) {
      first[i].level = second[i].level = i;
      std::cin >> first[i].value >> second[i].value;
      completed[i] = 0, first[i].priority = second[i].value;
    }

    std::sort(first.begin(), first.end(), compare());
    std::sort(second.begin(), second.end(), compare());

    int max = 0, moves = 0;
    while (!second.empty()) {
      while (!first.empty() && first.front().value <= max)
        third.push(first.front()), first.pop_front();

      if (!second.empty() && second.front().value <= max) {
        max += completed[second.front().level] ? 1 : 2, moves++;
        completed[second.front().level] = 2;
        second.pop_front();
      } else if (!third.empty()) {
        if (!completed[third.top().level])
          max++, moves++, completed[third.top().level] = 1;
        third.pop();
      } else {
        break;
      }
    }

    if (max < 2 * L) {
      printf("Case #%d: Too Bad\n", t + 1);
    } else {
      printf("Case #%d: %d\n", t + 1, moves);
    }
  }

  return 0;
}
