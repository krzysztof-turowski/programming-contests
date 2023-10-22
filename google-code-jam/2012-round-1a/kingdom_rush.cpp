#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

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
      while (!first.empty() && first.front().value <= max) {
        third.push(first.front()), first.pop_front();
      }
      if (!second.empty() && second.front().value <= max) {
        max += completed[second.front().level] ? 1 : 2, moves++;
        completed[second.front().level] = 2;
        second.pop_front();
      } else if (!third.empty()) {
        if (!completed[third.top().level]) {
          max++, moves++, completed[third.top().level] = 1;
        }
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
