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

int main() {
  int T;
  std::string text;

  std::cin >> T, std::getline(std::cin, text);
  REP(t, T) {
    std::getline(std::cin, text);
    int min = 0, max = 0;
    REP(i, text.length())
      if (text[i] == '(') {
        max++;
        if (i == 0 || text[i - 1] != ':')
          min++;
      } else if (text[i] == ')') {
        min = min ? min - 1 : 0;
        if (i == 0 || text[i - 1] != ':')
          max--;
        if (max < 0)
          break;
      }

    printf("Case #%d: %s\n", t + 1, (max >= 0) && (min == 0) ? "YES" : "NO");
  }

  return 0;
}
