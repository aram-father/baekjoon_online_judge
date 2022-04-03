#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Bulbs
{
private:
  size_t num_of_on_bulbs_;
  vector<string> bulbs_;

public:
  Bulbs(const vector<string>& bulbs) : num_of_on_bulbs_(0), bulbs_(bulbs)
  {
    for (int r = 0; r < 10; ++r)
    {
      for (int c = 0; c < 10; ++c)
      {
        if (bulbs[r][c] == 'O')
        {
          ++num_of_on_bulbs_;
        }
      }
    }
  }

  vector<string>& bulbs()
  {
    return bulbs_;
  }

  size_t num_of_on_bulbs() const
  {
    return num_of_on_bulbs_;
  }

  void Push(const int r, const int c)
  {
    const int dr[5] = { 0, -1, 0, 1, 0 };
    const int dc[5] = { 0, 0, 1, 0, -1 };

    for (int d = 0; d < 5; ++d)
    {
      int nr = r + dr[d];
      int nc = c + dc[d];

      if (0 <= nr && nr < 10 && 0 <= nc && nc < 10)
      {
        switch (bulbs_[nr][nc])
        {
          case 'O':
            bulbs_[nr][nc] = '#';
            --num_of_on_bulbs_;
            break;
          case '#':
            bulbs_[nr][nc] = 'O';
            ++num_of_on_bulbs_;
            break;
        }
      }
    }
  }
};

vector<string> BULBS(10, "");

int Solve()
{
  int answer = 10 * 10 + 1;

  for (int first_row_mask = 0; first_row_mask < (1 << 10); ++first_row_mask)
  {
    Bulbs bulbs(BULBS);

    int num_of_pushes = 0;

    // Process first row
    for (int col = 0; col < 10; ++col)
    {
      if (first_row_mask & (1 << col))
      {
        bulbs.Push(0, col);
        ++num_of_pushes;
      }
    }

    // Process remaining rows
    for (int row = 1; row < 10; ++row)
    {
      for (int col = 0; col < 10; ++col)
      {
        if (bulbs.bulbs()[row - 1][col] == 'O')
        {
          bulbs.Push(row, col);
          ++num_of_pushes;
        }
      }
    }

    if (bulbs.num_of_on_bulbs() == 0)
    {
      answer = min(answer, num_of_pushes);
    }
  }

  return answer > 100 ? -1 : answer;
}

int main(void)
{
  // Read input
  for (int row = 0; row < 10; ++row)
  {
    cin >> BULBS[row];
  }

  // Sovle
  cout << Solve() << endl;

  return 0;
}
