#include <iostream>
#include <set>
#include <vector>

bool check_word(
    std::string &S, const int &index, const int &L,
    const std::vector<std::set<char>> &D, const std::set<std::string> &W) {
  if (index == L) {
    return !W.count(S);
  }
  for (auto &c : D[index]) {
    S[index] = c;
    if (check_word(S, index + 1, L, D, W)) {
      return true;
    }
  }
  return false;
}

std::string solve(const std::set<std::string> &W, const int &L) {
  std::vector<std::set<char>> D(L);
  for (const auto &w : W) {
    for (int i = 0; i < L; i++) {
      D[i].insert(w[i]);
    }
  }
  std::string S(L, '-');
  bool found = check_word(S, 0, L, D, W);
  return found ? S : std::string(1, '-');
}

int main() {
  int T, N, L;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> N >> L, std::cin.ignore(256, '\n');
    std::set<std::string> W;
    for (int i = 0; i < N; i++) {
      std::string w;
      std::cin >> w, W.insert(w);
    }
    printf("Case #%d: %s\n", t + 1, solve(W, L).c_str());
  }
  return 0;
}
