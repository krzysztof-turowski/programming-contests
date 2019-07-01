#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int compute(const char &op, const int &L, const int &R) {
  if (op == '&') {
    return L & R;
  }
  if (op == '|') {
    return L | R;
  }
  return L ^ R;
}

int get(const char &x, const int &value) {
  if (x == '0') {
    return 0;
  }
  if (x == '1') {
    return 1;
  }
  if (x == 'x') {
    return value;
  }
  return 1 - value;
}

int construct(const std::string &S, const int &value, int &index) {
  if (S[index] == '(') {
    auto first = construct(S, value, ++index);
    char op = S[index];
    auto second = construct(S, value, ++index);
    ++index;
    return compute(op, first, second);
  }
  ++index;
  return get(S[index - 1], value);
}

int solve(const std::string &S) {
  int first = 0, second = 0;
  return construct(S, 0, first) != construct(S, 1, second);
}

int main() {
  int T;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::string S;
    std::cin >> S;
    printf("Case #%d: %d\n", t + 1, solve(S));
  }
  return 0;
}
