#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using llong = int64_t;

std::set<char> VOWELS{'a', 'e', 'i', 'o', 'u'};

llong solve(const std::string &L, const int &N) {
  std::vector<std::pair<int, int>> P;
  int consonants = 0;
  for (int i = 0; i < L.size(); i++) {
    if (!VOWELS.count(L[i])) {
      consonants++;
    } else {
      if (consonants >= N) {
        P.push_back(std::make_pair(i - consonants, i));
      }
      consonants = 0;
    }
  }
  if (consonants >= N) {
    P.push_back(std::make_pair(L.size() - consonants, L.size()));
  }
  llong out = 0;
  for (int i = 0, j = 0; i < L.size(); i++) {
    while (j < P.size() && P[j].second - i < N) {
      j++;
    }
    if (j == P.size()) {
      break;
    }
    out += L.size() - std::max(i, P[j].first) - N + 1;
  }
  return out;
}

int main() {
  int T;
  std::cin >> T, std::cin.ignore(256, '\n');
  for (int t = 0; t < T; t++) {
    int N;
    std::string L;
    std::cin >> L >> N;
    printf("Case #%d: %lld\n", t + 1, solve(L, N));
  }
  return 0;
}
