#include <iostream>

const int MAX = 501, MAX_ELEMENT = 50;
int A[MAX][MAX];

int main() {
  for (int i = 0; i < MAX; i++)
    for (int j = 0; j < MAX; j++)
      A[i][j] = 0;

  for (int i = 0; i < MAX_ELEMENT; i++)
    for (int j = 0; j < MAX_ELEMENT; j++) {
      if (i == 0 && j == 0)
        continue;
      for (int k = MAX - 1; k >= i; k--)
        for (int l = MAX - 1; l >= j; l--)
          A[k][l] = max(A[k][l], A[k - i][l - j] + 1);
      }

  int T, R, B;
  std::cin >> T;
  for (int t = 0; t < T; t++) {
    std::cin >> R >> B;
    printf("Case #%d: %d\n", t + 1, A[R][B]);
  }
}
