#include <cstdio>
#include <utility>
#include <queue>
#include <vector>

using namespace std;

const int kMaxW = 100;
const int kMaxH = 100;

vector<pair<int, int> > LASERS;
int W;
int H;
int VISIT[kMaxH][kMaxW];
char BOARD[kMaxH][kMaxW];
queue<pair<int, int> > Q;

const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

void Span(const int row, const int col, const int dir, const int cost)
{
  int nrow = row;
  int ncol = col;

  while (true)
  {
    nrow += dr[dir];
    ncol += dc[dir];

    if (0 > nrow || nrow >= H || 0 > ncol || ncol >= W || BOARD[nrow][ncol] == '*')
    {
      break;
    }

    if (VISIT[nrow][ncol] == -1)
    {
      VISIT[nrow][ncol] = cost;
      Q.emplace(nrow, ncol);
    }
  }
}

int Solve(void)
{
  VISIT[LASERS[0].first][LASERS[0].second] = 0;
  Q.push(LASERS[0]);
  for (int dir = 0; dir < 4; ++dir)
  {
    Span(LASERS[0].first, LASERS[0].second, dir, 0);
  }

  while (!Q.empty())
  {
    int row = Q.front().first;
    int col = Q.front().second;
    Q.pop();

    if (row == LASERS[1].first && col == LASERS[1].second)
    {
      return VISIT[row][col];
    }

    for (int dir = 0; dir < 4; ++dir)
    {
      Span(row, col, dir, VISIT[row][col] + 1);
    }
  }

  return -1;
}

int main(void)
{
  // Read Input
  scanf(" %d %d", &W, &H);
  for (int row = 0; row < H; ++row)
  {
    for (int col = 0; col < W; ++col)
    {
      scanf(" %c", &BOARD[row][col]);

      if (BOARD[row][col] == 'C')
      {
        LASERS.emplace_back(row, col);
      }

      VISIT[row][col] = -1;
    }
  }

  // Solve
  printf("%d\n", Solve());

  return 0;
}
