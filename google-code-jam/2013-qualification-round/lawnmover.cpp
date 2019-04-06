#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <stack>
#include <queue>

bool check(int **plansza, int u, int v, int a, int b) {
  bool value = true;
  for (int i = 0; i < a; i++)
    if (plansza[i][v] > plansza[u][v])
      value = false;
  if (value)
    return true;

  value = true;
  for (int i = 0; i < b; i++)
    if (plansza[u][i] > plansza[u][v])
      value = false;
  if (value)
    return true;

  return false;
}

int main() {
  int t;
  std::cin >> t;

  for (int s = 0; s < t; s++) {
    int a, b;
    std::cin >> a >> b;
    int **plansza = new int*[a];
    for (int i = 0; i < a; i++) {
      plansza[i] = new int[b];
      for (int j = 0; j < b; j++)
        std::cin >> plansza[i][j];
    }

    bool value = true;
    for (int i = 0; i < a; i++)
      for (int j = 0; j < b; j++)
        if (!check(plansza, i, j, a, b)) {
          value = false;
          break;
        }
    printf("Case #%d: %s\n", s + 1, value ? "YES" : "NO");

    for (int i = 0; i < a; i++)
      delete[] plansza[i];
    delete[] plansza;
  }

  return 0;
}
