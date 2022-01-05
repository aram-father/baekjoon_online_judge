#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class Board
{
public:
  const int kDR[4] = { -1, 0, 1, 0 };
  const int kDC[4] = { 0, 1, 0, -1 };

  int height_, width_;
  int hole_;
  pair<int, int> initial_balls_;
  vector<string> board_;

public:
  pair<int, int> ExpectMove(const int dir, const pair<int, int>& balls)
  {
    auto prev = balls;

    while (true)
    {
      int nred = (prev.first / width_ + kDR[dir]) * width_ + prev.first % width_ + kDC[dir];
      int nblue = (prev.second / width_ + kDR[dir]) * width_ + prev.second % width_ + kDC[dir];

      auto next = prev;
      if (prev.first != hole_ && board_[nred / width_][nred % width_] == '.' && nred != prev.second)
      {
        next.first = nred;
      }

      if (prev.second != hole_ && board_[nblue / width_][nblue % width_] == '.' &&
          (nblue != prev.first || prev.first == hole_))
      {
        next.second = nblue;
      }

      if (prev == next)
      {
        break;
      }

      prev = next;
    }

    return prev;
  }

  void ScanBoard()
  {
    cin >> height_ >> width_;

    board_.assign(height_, "");
    for (int r = 0; r < height_; ++r)
    {
      cin >> board_[r];
    }

    for (int r = 0; r < height_; ++r)
    {
      for (int c = 0; c < width_; ++c)
      {
        switch (board_[r][c])
        {
          case 'O':
            hole_ = r * width_ + c;
            board_[r][c] = '.';
            break;
          case 'R':
            initial_balls_.first = r * width_ + c;
            board_[r][c] = '.';
            break;
          case 'B':
            initial_balls_.second = r * width_ + c;
            board_[r][c] = '.';
            break;
        }
      }
    }
  }
};

int Solve(Board& board)
{
  queue<pair<int, int> > q;
  vector<vector<int> > visit(board.height_ * board.width_, vector<int>(board.height_ * board.width_, -1));

  q.emplace(board.initial_balls_);
  visit[board.initial_balls_.first][board.initial_balls_.second] = 0;

  while (!q.empty())
  {
    auto prev = q.front();
    q.pop();

    if (prev.second == board.hole_)
    {
      continue;
    }
    else if (prev.first == board.hole_)
    {
      return visit[prev.first][prev.second];
    }

    for (int dir = 0; dir < 4; ++dir)
    {
      auto next = board.ExpectMove(dir, prev);
      if (visit[next.first][next.second] == -1)
      {
        q.emplace(next);
        visit[next.first][next.second] = visit[prev.first][prev.second] + 1;
      }
    }
  }

  return -1;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  Board board;
  board.ScanBoard();

  // Solve
  cout << Solve(board) << '\n';

  return 0;
}
