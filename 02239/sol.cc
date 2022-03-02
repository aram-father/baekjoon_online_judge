#include <cstdio>

using namespace std;

const int kSize = 9;

int board[kSize][kSize];

void PrintBoard()
{
  for (int r = 0; r < kSize; ++r)
  {
    for (int c = 0; c < kSize; ++c)
    {
      printf("%d", board[r][c]);
    }
    printf("\n");
  }
}

bool Solve(const int idx)
{
  if (idx >= kSize * kSize)
  {
    PrintBoard();
    return true;
  }

  int row = idx / kSize;
  int col = idx % kSize;

  if (board[row][col] != 0)
  {
    return Solve(idx + 1);
  }

  bool used[kSize + 1] = {
    false,
  };

  for (int c = 0; c < kSize; ++c)
  {
    used[board[row][c]] = true;
  }

  for (int r = 0; r < kSize; ++r)
  {
    used[board[r][col]] = true;
  }

  int offset_row = 3 * (row / 3);
  int offset_col = 3 * (col / 3);
  for (int r = 0; r < 3; ++r)
  {
    for (int c = 0; c < 3; ++c)
    {
      used[board[offset_row + r][offset_col + c]] = true;
    }
  }

  for (int number = 1; number <= kSize; ++number)
  {
    if (!used[number])
    {
      board[row][col] = number;
      if (Solve(idx + 1))
      {
        return true;
      }
    }
  }

  board[row][col] = 0;
  return false;
}

int main(void)
{
  for (int r = 0; r < 9; ++r)
  {
    for (int c = 0; c < 9; ++c)
    {
      scanf(" %1d", &board[r][c]);
    }
  }

  Solve(0);

  return 0;
}
