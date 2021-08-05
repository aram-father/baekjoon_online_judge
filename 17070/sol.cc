#include <iostream>

using namespace std;

const size_t kMaxN = 16;
const size_t kH = 0;
const size_t kV = 1;
const size_t kD = 2;

size_t n;
size_t board[kMaxN][kMaxN];
size_t cache[kMaxN][kMaxN][3];

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> n;
  for (size_t r = 0; r < n; ++r)
  {
    for (size_t c = 0; c < n; ++c)
    {
      cin >> board[r][c];
    }
  }

  cache[0][1][kH] = 1;
  for (size_t r = 0; r < n; ++r)
  {
    for (size_t c = 0; c < n; ++c)
    {
      if (board[r][c] != 0)
      {
        continue;
      }

      if (1 <= c)
      {
        cache[r][c][kH] += cache[r][c - 1][kH];
        cache[r][c][kH] += cache[r][c - 1][kD];
      }
      if (1 <= r)
      {
        cache[r][c][kV] += cache[r - 1][c][kV];
        cache[r][c][kV] += cache[r - 1][c][kD];
      }
      if (1 <= c && 1 <= r)
      {
        if (board[r - 1][c] == 0 && board[r][c - 1] == 0)
        {
          cache[r][c][kD] += cache[r - 1][c - 1][kD];
          cache[r][c][kD] += cache[r - 1][c - 1][kH];
          cache[r][c][kD] += cache[r - 1][c - 1][kV];
        }
      }
    }
  }

  size_t answer = cache[n - 1][n - 1][kH] + cache[n - 1][n - 1][kV] + cache[n - 1][n - 1][kD];

  cout << answer << '\n';

  return 0;
}
