#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <vector>

class Interval {
 public:
  int left, height, length;
};

class Solution {
 public:
  int index, reachable;
  bool lucky;
};

std::pair<int, int> find_cave(const std::vector<std::string> &B, const char &cave) {
  for (size_t i = 0; i < B.size(); i++) {
    size_t index = B[i].find_first_of(cave);
    if (index != std::string::npos) {
      return std::make_pair(i, index);
    }
  }
  return std::make_pair(-1, -1);
}

std::vector<std::vector<bool>> get_reachable(
    const std::vector<std::string> &B, const std::pair<int, int> &X) {
  int R = B.size(), C = B[0].size();
  std::vector<std::vector<bool>> reachable(B.size());
  for (int i = 0; i < R; i++) {
    reachable[i] = std::vector<bool>(C, false);
  }
  std::stack<std::pair<int, int>> Q;
  Q.push(X);
  while (!Q.empty()) {
    auto p = Q.top();
    Q.pop();
    if (reachable[p.first][p.second]) {
      continue;
    }
    reachable[p.first][p.second] = true;
    for (int i = p.second - 1; i >= 0; i--) {
      if (B[p.first][i] == '#') {
        break;
      }
      Q.push(std::make_pair(p.first, i));
    }
    for (int i = p.second + 1; i < C; i++) {
      if (B[p.first][i] == '#') {
        break;
      }
      Q.push(std::make_pair(p.first, i));
    }
    if (B[p.first - 1][p.second] != '#') {
      Q.push(std::make_pair(p.first - 1, p.second));
    }
  }
  return reachable;
}

std::vector<Interval> get_start(const std::vector<std::vector<bool>> &reachable) {
  int R = reachable.size(), C = reachable[0].size();
  std::vector<Interval> P;
  for (int i = 0; i < R; i++) {
    Interval interval;
    interval.height = i;
    for (int j = 1; j < C; j++) {
      if (reachable[i][j] && !reachable[i][j - 1]) {
        interval.left = j;
      } else if (!reachable[i][j] && reachable[i][j - 1]) {
        interval.length = j - interval.left;
        P.push_back(interval);
      }
    }
  }
  return P;
}

int count(const std::vector<std::vector<bool>> &R) {
  int out = 0;
  for (const auto &row : R) {
    for (const auto &element : row) {
      if (element) {
        out++;
      }
    }
  }
  return out;
}

bool is_lucky(
    const std::vector<Interval> &P, const std::vector<std::vector<bool>> &R,
    const std::vector<std::string> &B) {
  std::vector<Interval> intervals(P);
  while (intervals.size() > 1) {
    std::vector<std::vector<int>> shifts;
    shifts.push_back(std::vector<int>(R[0].size(), 0));
    for (int length = R[0].size() - 1; length > 0; length--) {
      std::vector<int> next_shifts(length);
      for (int i = 0; i < length; i++) {
        next_shifts[i] = std::max(shifts.back()[i], shifts.back()[i + 1]);
        if (next_shifts[i] == -1) {
          continue;
        }
        for (const auto &interval : intervals) {
          if (interval.length == length) {
            if (B[interval.height + 1][interval.left + i] != '#') {
              if (R[interval.height + 1][interval.left + i]) {
                next_shifts[i] = 1;
              } else {
                next_shifts[i] = -1;
                break;
              }
            }
          }
        }
      }
      shifts.push_back(next_shifts);
    }
    if (shifts.back()[0] != 1) {
      return false;
    }
    std::vector<int> recovered(R[0].size(), 0);
    recovered[1] = 0;
    for (size_t i = 2, index = 0; i < R[0].size(); i++) {
      if (shifts[R[0].size() - i][index] == 1 || shifts[R[0].size() - i][index + 1] == -1) {
        recovered[i] = index;
      } else {
        recovered[i] = ++index;
      }
    }
    for (auto &interval : intervals) {
      if (B[interval.height + 1][interval.left + recovered[interval.length]] != '#') {
        interval.height++, interval.left += recovered[interval.length];
        while (B[interval.height][interval.left - 1] != '#') {
          interval.left--;
        }
        interval.length = 0;
        while (B[interval.height][interval.left + interval.length] != '#') {
          interval.length++;
        }
      }
    }
    auto it = std::unique(
        intervals.begin(), intervals.end(), [](const Interval& a, const Interval& b) {
      return a.left == b.left && a.length == b.length && a.height == b.height;
    });
    intervals.erase(it, intervals.end());
  }
  return true;
}

std::vector<Solution> solve(const std::vector<std::string> &B) {
  std::vector<Solution> solutions;
  for (int cave = 0; cave < 10; cave++) {
    const auto &X = find_cave(B, cave + '0');
    if (X.first == -1) {
      break;
    }
    std::vector<std::vector<bool>> R = get_reachable(B, X);
    std::vector<Interval> P = get_start(R);
    Solution S;
    S.index = cave, S.reachable = count(R);
    S.lucky = is_lucky(P, R, B);
    solutions.push_back(S);
  }
  return solutions;
}

int main() {
  int T, R, C;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> R >> C;
    std::vector<std::string> B(R);
    for (int i = 0; i < R; i++) {
      std::cin >> B[i];
    }
    std::vector<Solution> S = solve(B);
    printf("Case #%d:\n", t + 1);
    for (size_t i = 0; i < S.size(); i++) {
      printf("%d: %d %s\n", S[i].index, S[i].reachable, S[i].lucky ? "Lucky" : "Unlucky");
    }
  }
  return 0;
}
