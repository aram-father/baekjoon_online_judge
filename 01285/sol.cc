#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void FlipRow(const size_t row, vector<string>& coins)
{
  for (size_t col = 0; col < coins[0].size(); ++col)
  {
    coins[row][col] = coins[row][col] == 'H' ? 'T' : 'H';
  }
}

void FlipCol(const size_t col, vector<string>& coins)
{
  for (size_t row = 0; row < coins.size(); ++row)
  {
    coins[row][col] = coins[row][col] == 'H' ? 'T' : 'H';
  }
}

size_t CountTails(const vector<string>& coins, const int target_col = -1)
{
  size_t cnt = 0;
  for (size_t row = 0; row < coins.size(); ++row)
  {
    size_t begin = target_col != -1 ? target_col : 0;
    size_t end = target_col != -1 ? target_col + 1 : coins.size();

    for (size_t col = begin; col < end; ++col)
    {
      if (coins[row][col] == 'T')
      {
        ++cnt;
      }
    }
  }

  return cnt;
}

size_t Solve(vector<string>& coins)
{
  size_t answer = coins.size() * coins.size();

  for (size_t mask = 0; mask < ((size_t)1 << coins.size()); ++mask)
  {
    for (size_t hori = 0; hori < coins.size(); ++hori)
    {
      if (((size_t)1 << hori) & mask)
      {
        FlipRow(hori, coins);
      }
    }

    vector<size_t> fliped_cols;

    for (size_t vert = 0; vert < coins[0].size(); ++vert)
    {
      if (CountTails(coins, vert) > coins.size() / 2)
      {
        FlipCol(vert, coins);
        fliped_cols.emplace_back(vert);
      }
    }

    answer = min(answer, CountTails(coins));

    for (size_t hori = 0; hori < coins.size(); ++hori)
    {
      if (((size_t)1 << hori) & mask)
      {
        FlipRow(hori, coins);
      }
    }

    for (const auto& col : fliped_cols)
    {
      FlipCol(col, coins);
    }
  }

  return answer;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  size_t N;
  vector<string> COINS;

  cin >> N;

  COINS.assign(N, "");
  for (size_t it = 0; it < N; ++it)
  {
    cin >> COINS[it];
  }

  // Solve
  cout << Solve(COINS) << '\n';

  return 0;
}
