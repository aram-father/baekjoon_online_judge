#include <iostream>
#include <algorithm>
#include <limits>

using namespace std;

const int kMaxN = 1000;
const int kMaxM = 1000;

const int kL = 0;
const int kR = 1;
const int kU = 2;

const int kImpossible = -101 * kMaxN * kMaxM;

int n, m;
int mars[kMaxN][kMaxM];
int cache[kMaxN][kMaxM][3];

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> n >> m;

  for (int r = 0; r < n; ++r)
  {
    for (int c = 0; c < m; ++c)
    {
      cin >> mars[r][c];
    }
  }

  // Initialize
  for (int r = 0; r < n; ++r)
  {
    for (int c = 0; c < m; ++c)
    {
      cache[r][c][kL] = kImpossible;
      cache[r][c][kR] = kImpossible;
      cache[r][c][kU] = kImpossible;
    }
  }

  // Solve
  int sum = 0;
  for (int c = 0; c < m; ++c)
  {
    cache[0][c][kL] = sum + mars[0][c];
    sum += mars[0][c];
  }

  for (int r = 1; r < n; ++r)
  {
    for (int c = 0; c < m; ++c)
    {
      if (cache[r - 1][c][kL] != kImpossible)
      {
        cache[r][c][kU] = max(cache[r][c][kU], cache[r - 1][c][kL] + mars[r][c]);
      }
      if (cache[r - 1][c][kR] != kImpossible)
      {
        cache[r][c][kU] = max(cache[r][c][kU], cache[r - 1][c][kR] + mars[r][c]);
      }
      if (cache[r - 1][c][kU] != kImpossible)
      {
        cache[r][c][kU] = max(cache[r][c][kU], cache[r - 1][c][kU] + mars[r][c]);
      }
    }

    for (int c = 1; c < m; ++c)
    {
      if (cache[r][c - 1][kL] != kImpossible)
      {
        cache[r][c][kL] = max(cache[r][c][kL], cache[r][c - 1][kL] + mars[r][c]);
      }

      if (cache[r][c - 1][kU] != kImpossible)
      {
        cache[r][c][kL] = max(cache[r][c][kL], cache[r][c - 1][kU] + mars[r][c]);
      }
    }

    for (int c = m - 2; c >= 0; --c)
    {
      if (cache[r][c + 1][kR] != kImpossible)
      {
        cache[r][c][kR] = max(cache[r][c][kR], cache[r][c + 1][kR] + mars[r][c]);
      }

      if (cache[r][c + 1][kU] != kImpossible)
      {
        cache[r][c][kR] = max(cache[r][c][kR], cache[r][c + 1][kU] + mars[r][c]);
      }
    }
  }

  cout << max(cache[n - 1][m - 1][kL], max(cache[n - 1][m - 1][kR], cache[n - 1][m - 1][kU])) << '\n';

  return 0;
}
