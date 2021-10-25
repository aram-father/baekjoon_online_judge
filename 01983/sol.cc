#include <iostream>
#include <vector>
#include <iostream>

using namespace std;

const size_t kMaxN = 400 + 1;
const int kMinValue = -1 * (401 * 100 + 1);

size_t N;
vector<int> A;
vector<int> B;
int CACHE[kMaxN][kMaxN][kMaxN];

int Solve(void)
{
  if (A.size() == 0 || B.size() == 0)
  {
    return 0;
  }

  // Initialize
  for (size_t k = 0; k < kMaxN; ++k)
  {
    for (size_t i = 0; i < kMaxN; ++i)
    {
      for (size_t j = 0; j < kMaxN; ++j)
      {
        CACHE[k][i][j] = kMinValue;
      }
    }
  }

  for (size_t k = 0; k < kMaxN; ++k)
  {
    CACHE[k][0][0] = max(0, A[0] * B[0]);
  }
  CACHE[0][0][0] = A[0] * B[0];

  // Iteration
  for (size_t k = 1; k < N; ++k)
  {
    for (size_t i = 0; i < min(k + 1, A.size()); ++i)
    {
      for (size_t j = 0; j < min(k + 1, B.size()); ++j)
      {
        if (k > i && k > j)
        {
          CACHE[k][i][j] = max(CACHE[k][i][j], CACHE[k - 1][i][j]);
        }
        if (i != 0)
        {
          CACHE[k][i][j] = max(CACHE[k][i][j], CACHE[k - 1][i - 1][j]);
        }
        else if (k - 1 >= j)
        {
          CACHE[k][i][j] = max(CACHE[k][i][j], 0);
        }
        if (j != 0)
        {
          CACHE[k][i][j] = max(CACHE[k][i][j], CACHE[k - 1][i][j - 1]);
        }
        else if (k - 1 >= i)
        {
          CACHE[k][i][j] = max(CACHE[k][i][j], 0);
        }
        if (i != 0 && j != 0)
        {
          CACHE[k][i][j] = max(CACHE[k][i][j], CACHE[k - 1][i - 1][j - 1] + A[i] * B[j]);
        }
        else
        {
          CACHE[k][i][j] = max(CACHE[k][i][j], A[i] * B[j]);
        }
      }
    }
  }

  return CACHE[N - 1][A.size() - 1][B.size() - 1];
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;

  for (size_t it = 0; it < N; ++it)
  {
    int card;
    cin >> card;
    if (card != 0)
    {
      A.emplace_back(card);
    }
  }

  for (size_t it = 0; it < N; ++it)
  {
    int card;
    cin >> card;
    if (card != 0)
    {
      B.emplace_back(card);
    }
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
