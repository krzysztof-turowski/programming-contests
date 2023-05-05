#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <set>
#include <vector>

#define REP(i, n) for (int i = 0; i < (n); ++i)

#define MAX 26

int main() {
  int N;
  std::string text;

  std::cin >> N, std::getline(std::cin, text);
  REP(t, N) {
    std::getline(std::cin, text);

    std::vector<int> value(MAX);
    int sum = 0;

    REP(i, text.length())
      if (text[i] >= 'a' && text[i] <= 'z') {
        value[text[i] - 'a']++;
      } else if (text[i] >= 'A' && text[i] <= 'Z') {
        value[text[i] - 'A']++;
      }

    std::sort(value.begin(), value.end());
    REP(i, MAX)
      sum += (i + 1) * value[i];

    printf("Case #%d: %d\n", t + 1, sum);
  }

  return 0;
}
