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

using llong = int64_t;

const llong MAX = 10000001;

llong gcd(llong a, llong b) {
  return b != 0 ? gcd(b, a % b) : a;
}

class Dicts {
  std::vector<llong> low, high, low_count, high_count;

 public:
  Dicts() : low(MAX, LLONG_MAX - 1), high(MAX, -1), low_count(MAX, 0), high_count(MAX, 0) { }

  void insert(llong p, llong w, llong delta) {
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

  llong lowest() {
    llong out = 0, minimum = LLONG_MAX - 1;
    for (llong i = 0; i < MAX; i++) {
      if (minimum > low[i]) {
        out += low_count[i], minimum = low[i];
      }
    }
    return out;
  }

  llong highest() {
    llong out = 0, maximum = -1;
    for (llong i = MAX - 1; i >= 0; i--) {
      if (maximum < high[i]) {
        out += high_count[i], maximum = high[i];
      }
    }
    return out;
  }
};

void insert(std::deque<llong> &Q_min, std::deque<llong> &Q_max, llong w) {
  while (!Q_min.empty() && Q_min.back() > w) {
    Q_min.pop_back();
  }
  while (!Q_max.empty() && Q_max.back() < w) {
    Q_max.pop_back();
  }
  Q_min.push_back(w), Q_max.push_back(w);
}

void remove(std::deque<llong> &Q_min, std::deque<llong> &Q_max, llong w) {
  if (!Q_min.empty() && Q_min.front() == w) {
    Q_min.pop_front();
  }
  if (!Q_max.empty() && Q_max.front() == w) {
    Q_max.pop_front();
  }
}

void add(Dicts &S, std::vector<llong> &P, std::vector<llong> &W, llong length, llong delta) {
  while (length % P.size()) {
    --length;
    S.insert(P[length % P.size()], W[length % W.size()], delta);
  }
  length /= P.size();
  if (length == 0) {
    return;
  }
  for (int i = 0; i < gcd(P.size(), W.size()); i++) {
    std::deque<llong> Q_min, Q_max;
    llong first = i;
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

std::string solve(const std::vector<llong> &V) {
  llong p = V[1], w = V[2], n = V[0], index_p = -1, index_w = -1;
  std::vector<std::pair<llong, llong>> buffer;
  std::map<llong, llong> P_map, W_map;
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
    std::vector<llong> P, W;
    for (int i = index_p; i > 0; i--) {
      P.push_back(p);
      p = (V[5] * p + V[6]) % V[3] + 1;
    }
    for (int i = index_w; i > 0; i--) {
      W.push_back(w);
      w = (V[7] * w + V[8]) % V[4] + 1;
    }
    llong d = gcd(P.size(), W.size());
    llong m = static_cast<llong>(P.size()) / d * W.size();
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
  llong T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::vector<llong> V(9);
    for (int i = 0; i < 9; i++) {
      std::cin >> V[i];
    }
    printf("Case #%d: %s\n", t + 1, solve(V).c_str());
  }
  return 0;
}
