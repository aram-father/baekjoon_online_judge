#include <iostream>

using namespace std;

const int kMaxN = 14;
const int kRows = kMaxN * 2 + 1;
const int kCols = kMaxN * 2 + 1;

int CACHE[kMaxN + 1][kRows][kCols];

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Preprocess
  const int dr[2][6] = { { -1, 0, 1, 1, 0, -1 }, { -1, 0, 1, 1, 0, -1 } };
  const int dc[2][6] = { { 0, 1, 0, -1, -1, -1 }, { 1, 1, 1, 0, -1, 0 } };

  CACHE[0][kMaxN][kMaxN] = 1;

  for (int turn = 1; turn <= kMaxN; ++turn)
  {
    for (int row = 0; row < kRows; ++row)
    {
      for (int col = 0; col < kCols; ++col)
      {
        for (int dir = 0; dir < 6; ++dir)
        {
          int nrow = row + dr[row % 2][dir];
          int ncol = col + dc[row % 2][dir];
          if (0 > nrow || nrow >= kRows || 0 > ncol || ncol >= kCols)
          {
            continue;
          }

          CACHE[turn][row][col] += CACHE[turn - 1][nrow][ncol];
        }
      }
    }
  }

  int tc;
  cin >> tc;

  while (tc--)
  {
    int turn;
    cin >> turn;
    cout << CACHE[turn][kMaxN][kMaxN] << '\n';
  }

  return 0;
}
