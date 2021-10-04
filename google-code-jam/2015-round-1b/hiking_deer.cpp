#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

typedef int64_t llong;

class Hiker {
 public:
  int H;
  llong D, M;
};

class Event {
 public:
  llong time, cycle;
  int repeat;

  bool operator<(const Event& other) const {
      return time > other.time || (time == other.time && repeat < other.repeat);
  }
};

llong solve(std::vector<Hiker> &V) {
  std::priority_queue<Event> Q;
  int H = 0;
  for (int i = 0; i < V.size(); i++) {
    for (int j = 0; j < V[i].H; j++) {
      Event e{(360 - V[i].D) * (V[i].M + j), 360 * (V[i].M + j), 0};
      Q.push(e);
    }
    H += V[i].H;
  }
  int best = H, current = H;
  for (int i = 0; i < 2 * H; i++) {
    auto e = Q.top();
    Q.pop();
    if (e.repeat == 0) {
      current--, best = std::min(best, current);
    } else {
      current++;
    }
    Q.push(Event{e.time + e.cycle, e.cycle, e.repeat + 1});
  }
  return best;
}

int main() {
  int T, N;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N;
    std::vector<Hiker> V(N);
    for (int i = 0; i < N; i++) {
      std::cin >> V[i].D >> V[i].H >> V[i].M;
    }
    printf("Case #%d: %lld\n", t + 1, solve(V));
  }
  return 0;
}
