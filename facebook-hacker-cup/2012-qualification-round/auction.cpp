#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const int64 MAX = 10000001;

int64 gcd(int64 a, int64 b) {
  return b != 0 ? gcd(b, a % b) : a;
}

class Dicts {
  std::vector<int64> low, high, low_count, high_count;

 public:
  Dicts() : low(MAX, LLONG_MAX - 1), high(MAX, -1), low_count(MAX, 0), high_count(MAX, 0) { }

  void insert(int64 p, int64 w, int64 delta) {
    if (delta == 0) {
      return;
    }
    if (w < low[p]) {
      low[p] = w, low_count[p] = delta;
    } else if (w == low[p]) {
      low_count[p] += delta;
    }
    if (w > high[p]) {
      high[p] = w, high_count[p] = delta;
    } else if (w == high[p]) {
      high_count[p] += delta;
    }
  }

  int64 lowest() {
    int64 out = 0, minimum = LLONG_MAX - 1;
    for (int64 i = 0; i < MAX; i++) {
      if (minimum > low[i]) {
        out += low_count[i], minimum = low[i];
      }
    }
    return out;
  }

  int64 highest() {
    int64 out = 0, maximum = -1;
    for (int64 i = MAX - 1; i >= 0; i--) {
      if (maximum < high[i]) {
        out += high_count[i], maximum = high[i];
      }
    }
    return out;
  }
};

void insert(std::deque<int64> &Q_min, std::deque<int64> &Q_max, int64 w) {
  while (!Q_min.empty() && Q_min.back() > w) {
    Q_min.pop_back();
  }
  while (!Q_max.empty() && Q_max.back() < w) {
    Q_max.pop_back();
  }
  Q_min.push_back(w), Q_max.push_back(w);
}

void remove(std::deque<int64> &Q_min, std::deque<int64> &Q_max, int64 w) {
  if (!Q_min.empty() && Q_min.front() == w) {
    Q_min.pop_front();
  }
  if (!Q_max.empty() && Q_max.front() == w) {
    Q_max.pop_front();
  }
}

void add(Dicts &S, std::vector<int64> &P, std::vector<int64> &W, int64 length, int64 delta) {
  while (length % P.size()) {
    --length;
    S.insert(P[length % P.size()], W[length % W.size()], delta);
  }
  length /= P.size();
  if (length == 0) {
    return;
  }
  for (int i = 0; i < gcd(P.size(), W.size()); i++) {
    std::deque<int64> Q_min, Q_max;
    int64 first = i;
    for (int j = 0; j < length; j++) {
      insert(Q_min, Q_max, W[(first + j * P.size()) % W.size()]);
    }
    do {
      if (first < P.size()) {
        S.insert(P[first % P.size()], Q_min.front(), delta);
        if (Q_min.front() != Q_max.front()) {
          S.insert(P[first % P.size()], Q_max.front(), delta);
        }
      }
      remove(Q_min, Q_max, W[first]);
      insert(Q_min, Q_max, W[(first + length * P.size()) % W.size()]);
      first = (first + P.size()) % W.size();
    } while (first != i);
  }
}

std::string solve(const std::vector<int64> &V) {
  int64 p = V[1], w = V[2], n = V[0], index_p = -1, index_w = -1;
  std::vector<std::pair<int64, int64>> buffer;
  std::map<int64, int64> P_map, W_map;
  Dicts S;
  for (int i = 0; i < n; i++) {
    if (P_map.count(p) && W_map.count(w)) {
      index_p = i - P_map[p], index_w = i - W_map[w], n -= i;
      break;
    }
    buffer.push_back(std::make_pair(p, w));
    P_map[p] = i, W_map[w] = i;
    p = (V[5] * p + V[6]) % V[3] + 1, w = (V[7] * w + V[8]) % V[4] + 1;
  }
  if (index_p != -1 && index_w != -1) {
    std::vector<int64> P, W;
    for (int i = index_p; i > 0; i--) {
      P.push_back(p);
      p = (V[5] * p + V[6]) % V[3] + 1;
    }
    for (int i = index_w; i > 0; i--) {
      W.push_back(w);
      w = (V[7] * w + V[8]) % V[4] + 1;
    }
    int64 d = gcd(P.size(), W.size());
    int64 m = static_cast<int64>(P.size()) / d * W.size();
    if (P.size() > W.size()) {
      std::swap(P, W);
      for (int i = 0; i < buffer.size(); i++) {
        std::swap(buffer[i].first, buffer[i].second);
      }
    }
    add(S, P, W, m, n / m);
    add(S, P, W, n % m, 1);
  }
  for (auto &[p, w] : buffer) {
    S.insert(p, w, 1);
  }

  std::stringstream out;
  out << S.highest() << " " << S.lowest();
  return out.str();
}

int main() {
  int64 T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::vector<int64> V(9);
    for (int i = 0; i < 9; i++) {
      std::cin >> V[i];
    }
    printf("Case #%d: %s\n", t + 1, solve(V).c_str());
  }
  return 0;
}
