#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

std::string solve(const std::set<std::string> &C, const int &index) {
  std::set<std::string> R, S, P;
  for (const auto &s : C) {
    if (s[index % s.size()] == 'R') {
      R.insert(s);
    } else if (s[index % s.size()] == 'S') {
      S.insert(s);
    } else {
      P.insert(s);
    }
  }
  if (R.size() == 0 && S.size() == 0) {
    return "S";
  }
  if (R.size() == 0 && P.size() == 0) {
    return "R";
  }
  if (P.size() == 0 && S.size() == 0) {
    return "P";
  }
  if (R.size() == 0) {
    std::string out = solve(S, index + 1);
    if (out != "IMPOSSIBLE") {
      return "S" + out;
    }
  } else if (S.size() == 0) {
    std::string out = solve(P, index + 1);
    if (out != "IMPOSSIBLE") {
      return "P" + out;
    }
  } else if (P.size() == 0) {
    std::string out = solve(R, index + 1);
    if (out != "IMPOSSIBLE") {
      return "R" + out;
    }
  }
  return "IMPOSSIBLE";
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    int A = 0;
    std::string S;
    std::set<std::string> C;
    std::cin >> A, std::cin.ignore(256, '\n');
    for (int i = 0; i < A; i++) {
      std::cin >> S;
      C.insert(S);
    }
    printf("Case #%d: %s\n", t + 1, solve(C, 0).c_str());
  }
  return 0;
}
