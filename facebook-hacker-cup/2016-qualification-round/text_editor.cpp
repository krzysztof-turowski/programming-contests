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

typedef int64_t llong;

#define FOR(v, p, k) for (int v = p; v <= k; ++v)
#define FORD(v, p, k) for (int v = p; v >= k; --v)
#define REP(i, n) for (int i = 0; i < (n); ++i)
#define VAR(v, i) auto v = (i)
#define FOREACH(i, c) for (VAR(i, (c).begin()); i != (c).end(); ++i)

#define INFL 1000000000000000000LL

class PrePostFix {
 public:
  std::string prefix, first_postfix, second_postfix;

  PrePostFix(const std::string &a, const std::string &b) {
    auto positions = mismatch(a.begin(), a.end(), b.begin());

  prefix = a.substr(0, positions.first - a.begin());
  first_postfix = a.substr(positions.first - a.begin(), a.end() - positions.first);
  second_postfix = b.substr(positions.second - b.begin(), b.end() - positions.second);
  }
};

class PrefixNode {
 public:
  std::string prefix;
  bool used;
  std::vector<PrefixNode*> children;
  std::vector<llong> subwords;

  PrefixNode(const std::string &word, bool used) : prefix(word), used(used) { }
  ~PrefixNode() {
    REP(i, children.size()) {
      delete children[i];
    }
  }
};

class PrefixTree {
  PrefixNode *root;

 public:
  PrefixTree() : root(NULL) { }
  ~PrefixTree() {
    delete root;
  }

  void insert(std::string &word) {
    if (root == NULL) {
      root = new PrefixNode(word, true);
      return;
    }

    PrefixNode *current = root;
    while (current) {
      PrePostFix data(word, current->prefix);

      // Case 1: the word is equal to the node prefix
      if (data.first_postfix.length() == 0 && data.second_postfix.length() == 0) {
        current->used = true;
        return;
      // Case 2: the word is a proper substring of the node prefix
      } else if (data.first_postfix.length() == 0) {
        PrefixNode *oldNode = new PrefixNode(data.second_postfix, current->used);
        oldNode->children = current->children;

        current->prefix = data.prefix;
        current->used = true;
        current->children.clear();
        current->children.push_back(oldNode);

        return;
      // Case 3: the word is a proper superstring of node prefix
      } else if (data.second_postfix.length() == 0) {
        // Find if there is a child with longer prefix matching the word
        char c = data.first_postfix[0];
        int index = -1;
        REP(i, current->children.size())
          if (current->children[i]->prefix[0] == c) {
            index = i;
            break;
          }

        // If yes, recurse on it -- if no, append new child
        if (index >= 0) {
          current = current->children[index];
          word = data.first_postfix;
        } else {
          current->children.push_back(new PrefixNode(data.first_postfix, true));
          return;
        }
      // Case 4: the word and the node prefix match partially (both postfixes are non-empty)
      } else {
        PrefixNode *newNode = new PrefixNode(data.first_postfix, true);
        PrefixNode *oldNode = new PrefixNode(data.second_postfix, current->used);
        oldNode->children = current->children;

        current->prefix = data.prefix;
        current->used = false;
        current->children.clear();
        current->children.push_back(oldNode);
        current->children.push_back(newNode);

        return;
      }
    }
  }

  llong compute(int K) {
    compute(root);
    return root->subwords[K];
  }

  void print() {
    print(root, 0);
  }

  void print(PrefixNode *current, const int &offset = 0) {
    std::string spaces(offset, ' ');
    std::cout << spaces << current->prefix << std::endl;
    FOREACH(e, current->children)
      print(*e, offset + 2);
  }

 private:
  void compute(PrefixNode *current) {
    current->subwords.push_back(0L);
    if (current->used) {
      current->subwords.push_back(0L);
    }
    FOREACH(e, current->children) {
      compute(*e);
      join(current->subwords, (*e)->subwords);
    }
    FOR(i, 1, current->subwords.size() - 1) {
      current->subwords[i] += 2 * current->prefix.length();
    }
  }

  void join(std::vector<llong> &first, std::vector<llong> &second) {
    std::vector<llong> result(first.size() + second.size() - 1, INFL);
    REP(i, first.size()) {
      REP(j, second.size()) {
        result[i + j] = std::min(result[i + j], first[i] + second[j]);
      }
    }
    first.assign(result.begin(), result.end());
  }
};

llong solve() {
  int N, K;
  std::cin >> N >> K;
  PrefixTree T;
  REP(i, N) {
    std::string word;
    std::cin >> word;
    T.insert(word);
  }
  return T.compute(K) + K;
}

int main() {
  int T;
  std::cin >> T;
  REP(t, T)  {
    printf("Case #%d: %lld\n", t + 1, solve());
  }
  return 0;
}
