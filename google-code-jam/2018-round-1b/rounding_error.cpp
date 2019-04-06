#include <algorithm>
#include <iostream>
#include <vector>

#define INF 10000000

struct language {
 public:
  int users, needed_to_round;

  language() {
    this->users = 0, this->needed_to_round = 0;
  }

  language(const int &users, const int &needed_to_round) {
    this->users = users, this->needed_to_round = needed_to_round;
  }

  bool operator<(const language& other) const {
    return needed_to_round < other.needed_to_round;
  }
};

int find_round(const int &C, const int &N) {
  for (int i = 0; i < N; i++)
    if ((100.0 * (C + i) / N) - (100 * (C + i) / N) >= 0.5) {
      return i;
    }
  return INF;
}

int solve(const int &N, const int &L, std::vector<language> &C) {
  int remainder = N;
  for (int i = 0; i < L; i++)
    remainder -= C[i].users;

  int Y = find_round(0, N);
  std::vector<language> X(remainder / Y + 1, {0, Y});
  for (int i = 0; i < C.size(); i++)
    C[i].needed_to_round = find_round(C[i].users, N);
  X.insert(X.end(), C.begin(), C.end());
  std::sort(X.begin(), X.end());

  int sum = 0;
  for (int i = 0; i < X.size(); i++) {
    if (remainder >= X[i].needed_to_round) {
      remainder -= X[i].needed_to_round;
      sum += (100 * (X[i].users + X[i].needed_to_round) / N) + 1;
    } else {
      sum += 100 * X[i].users / N;
    }
  }
  sum += 100 * remainder / N;
  return sum;
}

int main() {
  int T, N, L;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> L;
    std::vector<language> C(L);
    for (int i = 0; i < L; i++) {
      std::cin >> C[i].users;
    }
    printf("Case #%d: %d\n", t + 1, solve(N, L, C));
  }
}
