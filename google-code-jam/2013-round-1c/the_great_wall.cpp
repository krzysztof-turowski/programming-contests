#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>

const int MAX = 1 << 29;

class Attack {
 public:
  int east, west, strength;

  Attack(const int &west_v, const int &east_v, const int &strength_v)
      : west(west_v), east(east_v), strength(strength_v) { }

  Attack(const Attack &other, const int &move_d, const int &strength_d, const int &round)
      : west(other.west + round * move_d), east(other.east + round * move_d),
          strength(other.strength + round * strength_d) { }
};

bool operator <(const Attack &first, const Attack &second) {
  return true;
}

class IntervalTree {
 public:
  int west, east, min_height = 0;
  IntervalTree *left = NULL, *right = NULL;

  IntervalTree() : west(0), east(2 * MAX - 1) { }
  IntervalTree(const int &west_v, const int &east_v) : west(west_v), east(east_v) { }

  bool is_success(const Attack &attack) {
    if (attack.west >= west && attack.east <= east + 1 && attack.strength <= min_height) {
      return false;
    }
    if (attack.west == west && attack.east == east + 1) {
      return attack.strength > min_height;
    }
    int mid = (east + west) / 2;
    bool left_value = false, right_value = false;
    if (attack.west <= mid) {
      if (left == NULL) {
        left = new IntervalTree(west, mid);
      }
      left_value = left->is_success(
          Attack(attack.west, std::min(attack.east, mid + 1), attack.strength));
    }
    if (attack.east > mid + 1) {
      if (right == NULL) {
        right = new IntervalTree(mid + 1, east);
      }
      right_value = right->is_success(
          Attack(std::max(attack.west, mid + 1), attack.east, attack.strength));
    }
    return left_value || right_value;
  }

  void update(const Attack &attack) {
    if (attack.west == west && attack.east == east + 1) {
      min_height = std::max(min_height, attack.strength);
      return;
    }
    int mid = (east + west) / 2;
    if (attack.west <= mid) {
      if (left == NULL) {
        left = new IntervalTree(west, mid);
      }
      left->update(
          Attack(attack.west, std::min(attack.east, mid + 1), attack.strength));
    }
    if (attack.east > mid + 1) {
      if (right == NULL) {
        right = new IntervalTree(mid + 1, east);
      }
      right->update(
          Attack(std::max(attack.west, mid + 1), attack.east, attack.strength));
    }
    min_height = std::max(
        min_height, std::min(left ? left->min_height : 0, right ? right->min_height : 0));
  }

  ~IntervalTree() {
    if (left) {
      delete left;
    }
    if (right) {
      delete right;
    }
  }
};

int solve(std::priority_queue<std::pair<int, Attack>> &Q) {
  int out = 0;
  IntervalTree T;
  while (!Q.empty()) {
    int day = Q.top().first;
    std::vector<Attack> update;
    while (!Q.empty() && Q.top().first == day) {
      if (T.is_success(Q.top().second)) {
        out++, update.push_back(Q.top().second);
      }
      Q.pop();
    }
    for (const auto &attack : update) {
      T.update(attack);
    }
  }
  return out;
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int N;
    std::cin >> N;
    std::priority_queue<std::pair<int, Attack>> Q;
    for (int i = 0; i < N; i++) {
      int di, ni, wi, ei, si, delta_di, delta_pi, delta_si;
      std::cin >> di >> ni >> wi >> ei >> si >> delta_di >> delta_pi >> delta_si;
      const auto &attack = Attack(wi + MAX, ei + MAX, si);
      for (int j = 0; j < ni; j++) {
        Q.push(std::make_pair(-di - j * delta_di, Attack(attack, delta_pi, delta_si, j)));
      }
    }
    printf("Case #%d: %d\n", t + 1, solve(Q));
  }
  return 0;
}
