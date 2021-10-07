#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>

using namespace std;

const int kMaxN = 500;

int N;
int WOODS[kMaxN][kMaxN];
int64_t CACHE[kMaxN][kMaxN];

bool IsSafe(const int row, const int col)
{
  if (0 > row || row >= N || 0 > col || col >= N)
  {
    return false;
  }

  return true;
}

int64_t Solve(const int row, const int col)
{
  int64_t& ret = CACHE[row][col];

  if (ret != -1)
  {
    return ret;
  }

  ret = 1;

  const int dr[4] = { -1, 0, 1, 0 };
  const int dc[4] = { 0, 1, 0, -1 };

  for (int d = 0; d < 4; ++d)
  {
    int nrow = row + dr[d];
    int ncol = col + dc[d];

    if (IsSafe(nrow, ncol) && WOODS[row][col] < WOODS[nrow][ncol])
    {
      ret = max(ret, 1 + Solve(nrow, ncol));
    }
  }

  return ret;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;
  for (int r = 0; r < N; ++r)
  {
    for (int c = 0; c < N; ++c)
    {
      cin >> WOODS[r][c];
      CACHE[r][c] = -1;  ///< Initialize
    }
  }

  // Solve
  int64_t ans = -1;
  for (int r = 0; r < N; ++r)
  {
    for (int c = 0; c < N; ++c)
    {
      ans = max(ans, Solve(r, c));
    }
  }

  cout << ans << '\n';

  return 0;
}
