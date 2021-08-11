#include <iostream>

using namespace std;

const int kMod = 1000007;

int N, M, C;
int board[51][51];
int cache[51][51][51][51];

int Solve(const int row, const int col, const int i, const int k)
{
  if (row < 1 || row > N || col < 1 || col > M)
  {
    return 0;
  }

  if (row == 1 && col == 1)
  {
    if (board[row][col] == -1)
    {
      if (k == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
    else
    {
      if (k == 1 && board[row][col] <= i)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
  }

  int& ret = cache[row][col][i][k];

  if (ret == -1)
  {
    ret = 0;

    if (board[row][col] == -1)
    {
      ret += Solve(row - 1, col, i, k);
      ret %= kMod;
      ret += Solve(row, col - 1, i, k);
      ret %= kMod;
    }
    else if (i >= board[row][col])
    {
      ret += Solve(row - 1, col, board[row][col] - 1, k - 1);
      ret %= kMod;
      ret += Solve(row, col - 1, board[row][col] - 1, k - 1);
      ret %= kMod;
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

  // Initialize
  for (int row = 0; row < 51; ++row)
  {
    for (int col = 0; col < 51; ++col)
    {
      board[row][col] = -1;

      for (int i = 0; i < 51; ++i)
      {
        for (int k = 0; k < 51; ++k)
        {
          cache[row][col][i][k] = -1;
        }
      }
    }
  }

  // Read input
  cin >> N >> M >> C;

  for (int it = 1; it <= C; ++it)
  {
    int row, col;
    cin >> row >> col;
    board[row][col] = it;
  }

  // Solve
  for (int k = 0; k <= C; ++k)
  {
    cout << Solve(N, M, C, k) % kMod << ' ';
  }
  cout << '\n';

  return 0;
}
