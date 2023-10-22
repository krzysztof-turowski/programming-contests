#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <cmath>
#include <map>

using llong = int64_t;
using ldouble = long double;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define SIZE(x) static_cast<int>(x.size())

int main() {
  int T;

  std::string line;
  const std::string text = std::string("ourlanguageisimpossibletounderstandthereare")
      + std::string("twentysixfactorialpossibilitiessoitisokayifyouwanttojustgiveup");
  const std::string cipher = std::string("ejpmysljylckdkxveddknmcrejsicpdrysirbcpcypc")
      + std::string("rtcsradkhwyfrepkymveddknkmkrkcddekrkdeoyakwaejtysrreujdrlkgcjv");
  std::map<char, char> reverse;

  FORD(i, SIZE(text) - 1, 0) {
    reverse[cipher[i]] = text[i];
  }
  reverse['q'] = 'z', reverse['z'] = 'q';

  std::cin >> T;
  REP(t, T) {
    std::getline(std::cin, line);
    FORD(i, SIZE(line) - 1, 0) {
      if (line[i] <= 'z' && line[i] >= 'a') {
        line[i] = reverse[line[i]];
      }
    }
    printf("Case #%d: %s\n", t + 1, line.c_str());
  }

  return 0;
}
