#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

int solve(const int &servers, const std::vector<std::string> &queries) {
  int out = 0;
  std::set<std::string> used;
  for (size_t i = 0; i < queries.size(); i++) {
    used.insert(queries[i]);
    if (used.size() == servers) {
      used.clear(), used.insert(queries[i]), out++;
    }
  }
  return out;
}

int main() {
  int T, S, Q;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> S, std::cin.ignore(256, '\n');
    std::vector<std::string> servers(S);
    for (int i = 0; i < S; i++) {
      std::getline(std::cin, servers[i]);
    }
    std::cin >> Q, std::cin.ignore(256, '\n');
    std::vector<std::string> queries(Q);
    for (int i = 0; i < Q; i++) {
      std::getline(std::cin, queries[i]);
    }
    printf("Case #%d: %d\n", t + 1, solve(servers.size(), queries));
  }
  return 0;
}
