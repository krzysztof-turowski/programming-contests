#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <cassert>

using llong = int64_t;
using ldouble = long double;
using vldouble = std::vector<ldouble>;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)

const ldouble INF = 1000000000, EPS = 1e-5;

struct car {
  int lane;
  ldouble speed, position;

  ldouble distance(const ldouble &time) const {
    return position + speed * time;
  }
};

struct sort_first {
  static ldouble time;

  bool operator()(const car &a, const car &b) const {
    if (fabs(a.distance(time) - b.distance(time)) < EPS) {
      return a.speed < b.speed;
    }
    return a.distance(time) < b.distance(time);
  }
};

ldouble sort_first::time = 0;

bool collide(const car &a, const car &b, const ldouble &time) {
  ldouble pa = a.distance(time), pb = b.distance(time);
  assert(pa <= pb + EPS);
  return fabs(pa - pb) < 5;
}

bool touch_collide(const car &a, const car &b, const ldouble &time) {
  ldouble pa = a.distance(time), pb = b.distance(time);
  assert(pa <= pb + EPS);
  return fabs(pa - pb) < 5 || (fabs(pa - pb + 5) < EPS && a.speed > b.speed);
}

inline ldouble start_time(const car &a, const car &b) {
  assert(a.position <= b.position);
  return (a.position - b.position + 5) / (b.speed - a.speed);
}

inline ldouble stop_time(const car &a, const car &b) {
  assert(a.position <= b.position);
  return (a.position - b.position - 5) / (b.speed - a.speed);
}

inline void set_unknown(std::vector<car> &C, const int &N, const ldouble &time) {
  REP(i, N) {
    if ((i == 0 || !collide(C[i - 1], C[i], sort_first::time))
        && (i == N - 1 || !collide(C[i], C[i + 1], sort_first::time))) {
      C[i].lane = 0;
    }
  }
}

ldouble solve(std::vector<car> &C, const int &N) {
  sort_first::time = 0;
  std::sort(C.begin(), C.end(), sort_first());
  set_unknown(C, N, 0);

  ldouble time;
  vldouble Q;
  REP(i, N) FOR(j, i + 1, N - 1) {
    time = start_time(C[i], C[j]);
    if (time >= -EPS && C[i].speed != C[j].speed) {
      Q.push_back(time);
    }
    time = stop_time(C[i], C[j]);
    if (time >= -EPS && C[i].speed != C[j].speed) {
      Q.push_back(time);
    }
  }
  std::sort(Q.begin(), Q.end()), Q.erase(std::unique(Q.begin(), Q.end()), Q.end());

  int group = 1;
  for (auto it : Q) {
    sort_first::time = it;
    std::sort(C.begin(), C.end(), sort_first());

    vldouble D(N);
    REP(i, N) {
      D[i] = C[i].distance(it);
    }
    set_unknown(C, N, it);

    REP(i, N) FOR(j, i + 1, N - 1) {
      if (touch_collide(C[i], C[j], it)) {
        if (C[i].lane > 0 && C[i].lane == C[j].lane) {
          return it;
        }
        if (C[i].lane >= INF) {
          if (C[j].lane > 0) {
            FOR(k, j + 1, N - 1) {
              if (C[j].lane / 2 == C[k].lane / 2) {
                C[k].lane = C[i].lane - (2 * (C[i].lane % 2) - 1) * (C[j].lane == C[k].lane);
              }
            }
          }
          C[j].lane = C[i].lane - (2 * (C[i].lane % 2) - 1);
        } else if (C[i].lane > 0 && C[j].lane < INF) {
          C[j].lane = C[i].lane - (2 * (C[i].lane % 2) - 1);
        }
      }
    }

    FORD(i, N - 1, 0) FORD(j, i - 1, 0) {
      if (touch_collide(C[j], C[i], it)) {
        if (C[i].lane > 0 && C[i].lane == C[j].lane) {
          return it;
        }
        if (C[i].lane >= INF) {
          if (C[j].lane > 0) {
            FORD(k, j - 1, 0) {
              if (C[j].lane / 2 == C[k].lane / 2) {
                C[k].lane = C[i].lane - (2 * (C[i].lane % 2) - 1) * (C[j].lane == C[k].lane);
              }
            }
          }
          C[j].lane = C[i].lane - (2 * (C[i].lane % 2) - 1);
        } else if (C[i].lane > 0 && C[j].lane < INF) {
          C[j].lane = C[i].lane - (2 * (C[i].lane % 2) - 1);
        } else {
          C[i].lane = ++group, C[j].lane = ++group;
        }
      }
    }
  }
  return INF;
}

int main() {
  int T;

  scanf("%d\n", &T);
  REP(t, T) {
    int N;
    scanf("%d\n", &N);

    std::vector<car> C(N);
    char lane;
    REP(i, N) {
      scanf("%c %Lf %Lf\n", &lane, &C[i].speed, &C[i].position);
      C[i].lane = lane == 'L' ? INF : INF + 1;
    }

    ldouble time = solve(C, N);
    if (time == INF) {
      printf("Case #%d: Possible\n", t + 1);
    } else {
      printf("Case #%d: %.6Lf\n", t + 1, time);
    }
  }

  return 0;
}
