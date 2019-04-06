#include <iostream>
#include <string>
#include <cstdio>

bool check(const std::string *board, const char &element) {
  for (int i = 0; i < 4; i++) {
    bool line = true;
    for (int j = 0; j < 4; j++)
      if (board[i][j] != 'T' && board[i][j] != element)
        line = false;
    if (line)
      return true;
  }

  for (int i = 0; i < 4; i++) {
    bool line = true;
    for (int j = 0; j < 4; j++)
      if (board[j][i] != 'T' && board[j][i] != element)
        line = false;
    if (line)
      return true;
  }

  bool line = true;
  for (int j = 0; j < 4; j++)
    if (board[j][j] != 'T' && board[j][j] != element)
      line = false;
  if (line)
    return true;

  line = true;
  for (int j = 0; j < 4; j++)
    if (board[j][3 - j] != 'T' && board[j][3 - j] != element)
      line = false;
  if (line)
    return true;

  return false;
}

int main() {
  int T;
  std::cin >> T;

  for (int t = 0; t < T; t++) {
    std::string *board = new std::string[4];
    for (int i = 0; i < 4; i++)
      std::cin >> board[i];

    int k = 0;
    for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
        if (board[i][j] == '.')
          k++;

    if (check(board, 'X')) {
      printf("Case #%d: X won\n", t + 1);
    } else if (check(board, 'O')) {
      printf("Case #%d: O won\n", t + 1);
    } else if (k == 0) {
      printf("Case #%d: Draw\n", t + 1);
    } else {
      printf("Case #%d: Game has not completed\n", t + 1);
    }
    delete[] board;
  }

  return 0;
}
