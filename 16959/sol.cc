#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

const int kMaxN = 10;
const int kKnight = 0;
const int kBishop = 1;
const int kRook = 2;
const int kNumOfPieceKinds = 3;

struct Piece
{
  int row;
  int col;
  int kind;
  int target;
  int elapsed;

  Piece(const int row, const int col, const int kind, const int target, const int elapsed)
    : row(row), col(col), kind(kind), target(target), elapsed(elapsed)
  {
  }
};

int N;
int BOARD[kMaxN][kMaxN];
map<int, pair<int, int> > POS;

int Bfs(void)
{
  bool visit[kMaxN][kMaxN][kMaxN * kMaxN + 1][kNumOfPieceKinds] = {
    false,
  };
  queue<Piece> q;

  visit[POS[1].first][POS[1].second][1][kKnight] = true;
  visit[POS[1].first][POS[1].second][1][kBishop] = true;
  visit[POS[1].first][POS[1].second][1][kRook] = true;

  q.emplace(POS[1].first, POS[1].second, kBishop, 2, 0);
  q.emplace(POS[1].first, POS[1].second, kRook, 2, 0);
  q.emplace(POS[1].first, POS[1].second, kKnight, 2, 0);

  int ans = -1;

  while (!q.empty())
  {
    Piece current = q.front();
    q.pop();

    if (current.target == N * N && BOARD[current.row][current.col] == N * N)
    {
      ans = current.elapsed;
      break;
    }

    int ntarget = current.target;
    if (BOARD[current.row][current.col] == current.target)
    {
      ntarget = ntarget + 1;
    }

    if (current.kind == kKnight)
    {
      const int dr[8] = { -2, -1, 1, 2, 2, 1, -1, -2 };
      const int dc[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

      for (int dir = 0; dir < 8; ++dir)
      {
        int nrow = current.row + dr[dir];
        int ncol = current.col + dc[dir];
        if (0 <= nrow && nrow < N && 0 <= ncol && ncol < N)
        {
          if (!visit[nrow][ncol][ntarget][kKnight])
          {
            visit[nrow][ncol][ntarget][kKnight] = true;
            q.emplace(nrow, ncol, kKnight, ntarget, current.elapsed + 1);
          }
        }
      }

      if (!visit[current.row][current.col][ntarget][kBishop])
      {
        visit[current.row][current.col][ntarget][kBishop] = true;
        q.emplace(current.row, current.col, kBishop, ntarget, current.elapsed + 1);
      }

      if (!visit[current.row][current.col][ntarget][kRook])
      {
        visit[current.row][current.col][ntarget][kRook] = true;
        q.emplace(current.row, current.col, kRook, ntarget, current.elapsed + 1);
      }
    }
    else if (current.kind == kBishop)
    {
      const int dr[4] = { -1, 1, 1, -1 };
      const int dc[4] = { 1, 1, -1, -1 };

      for (int dir = 0; dir < 4; ++dir)
      {
        int nrow = current.row;
        int ncol = current.col;
        while (true)
        {
          nrow += dr[dir];
          ncol += dc[dir];
          if (0 <= nrow && nrow < N && 0 <= ncol && ncol < N)
          {
            if (!visit[nrow][ncol][ntarget][kBishop])
            {
              visit[nrow][ncol][ntarget][kBishop] = true;
              q.emplace(nrow, ncol, kBishop, ntarget, current.elapsed + 1);
            }
          }
          else
          {
            break;
          }
        }
      }

      if (!visit[current.row][current.col][ntarget][kKnight])
      {
        visit[current.row][current.col][ntarget][kKnight] = true;
        q.emplace(current.row, current.col, kKnight, ntarget, current.elapsed + 1);
      }

      if (!visit[current.row][current.col][ntarget][kRook])
      {
        visit[current.row][current.col][ntarget][kRook] = true;
        q.emplace(current.row, current.col, kRook, ntarget, current.elapsed + 1);
      }
    }
    else if (current.kind == kRook)
    {
      const int dr[4] = { -1, 0, 1, 0 };
      const int dc[4] = { 0, 1, 0, -1 };

      for (int dir = 0; dir < 4; ++dir)
      {
        int nrow = current.row;
        int ncol = current.col;
        while (true)
        {
          nrow += dr[dir];
          ncol += dc[dir];
          if (0 <= nrow && nrow < N && 0 <= ncol && ncol < N)
          {
            if (!visit[nrow][ncol][ntarget][kRook])
            {
              visit[nrow][ncol][ntarget][kRook] = true;
              q.emplace(nrow, ncol, kRook, ntarget, current.elapsed + 1);
            }
          }
          else
          {
            break;
          }
        }
      }

      if (!visit[current.row][current.col][ntarget][kKnight])
      {
        visit[current.row][current.col][ntarget][kKnight] = true;
        q.emplace(current.row, current.col, kKnight, ntarget, current.elapsed + 1);
      }

      if (!visit[current.row][current.col][ntarget][kBishop])
      {
        visit[current.row][current.col][ntarget][kBishop] = true;
        q.emplace(current.row, current.col, kBishop, ntarget, current.elapsed + 1);
      }
    }
  }

  return ans;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;
  for (int i = 0; i < N * N; ++i)
  {
    cin >> BOARD[i / N][i % N];
    POS[BOARD[i / N][i % N]] = pair<int, int>(i / N, i % N);
  }

  // Solve
  cout << Bfs() << '\n';

  return 0;
}
