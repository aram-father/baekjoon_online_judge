#include <iostream>
#include <vector>

using namespace std;

class Board
{
public:
  enum CellType
  {
    kPuttable = 1,
    kNonPuttable = 0,
    kBishop = 2
  };

private:
  int size_;
  vector<vector<int> > board_;
  vector<bool> inc_diags_;
  vector<bool> dec_diags_;

public:
  Board(const size_t size)
    : size_((int)size)
    , board_(size, vector<int>(size, kPuttable))
    , inc_diags_(2 * size - 1, false)
    , dec_diags_(2 * size - 1, false)
  {
  }

  int size() const
  {
    return size_;
  }

  vector<vector<int> >& board()
  {
    return board_;
  }

  bool IsPuttable(const int row, const int col)
  {
    return board_[row][col] == kPuttable && !inc_diags_[row + col] && !dec_diags_[row - col + size_ - 1];
  }

  void PutDownBishop(const int row, const int col)
  {
    board_[row][col] = kBishop;
    inc_diags_[row + col] = true;
    dec_diags_[row - col + size_ - 1] = true;
  }

  void PutAwayBishop(const int row, const int col)
  {
    board_[row][col] = kPuttable;
    inc_diags_[row + col] = false;
    dec_diags_[row - col + size_ - 1] = false;
  }
};

int Solve(int index, Board& board)
{
  if (index >= board.size() * board.size())
  {
    return 0;
  }

  int row = index / board.size();
  int col = index % board.size();

  int next_index = index + 2;
  if (board.size() % 2 == 0 && col + 2 >= board.size())
  {
    next_index = (row + 1) * board.size() + (col % 2 ? 0 : 1);
  }

  if (!board.IsPuttable(row, col))
  {
    return Solve(next_index, board);
  }
  else
  {
    board.PutDownBishop(row, col);
    int put = 1 + Solve(next_index, board);

    board.PutAwayBishop(row, col);
    int not_put = Solve(next_index, board);

    return put < not_put ? not_put : put;
  }
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  size_t n;
  cin >> n;

  Board board(n);
  for (size_t row = 0; row < n; ++row)
  {
    for (size_t col = 0; col < n; ++col)
    {
      cin >> board.board()[row][col];
    }
  }

  // Solve
  cout << Solve(0, board) + Solve(1, board) << '\n';

  return 0;
}
