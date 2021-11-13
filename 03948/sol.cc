#include <iostream>
#include <cstdint>

using namespace std;

const int kMaxN = 20;

int N;
int64_t CACHE[2][kMaxN + 1];

int64_t nCr[kMaxN + 1][kMaxN + 1];

void Initialize(void)
{
  for (int n = 0; n <= kMaxN; ++n)
  {
    nCr[n][0] = 1;
  }

  for (int n = 1; n <= kMaxN; ++n)
  {
    for (int r = 1; r <= n; ++r)
    {
      nCr[n][r] = nCr[n - 1][r] + nCr[n - 1][r - 1];
    }
  }
}

int64_t Solve(const int type, const int n)
{
  if (n <= 1)
  {
    return 1;
  }

  int64_t& ret = CACHE[type][n];

  if (ret != -1)
  {
    return ret;
  }

  ret = 0;
  for (int left = type; left < n; left += 2)
  {
    int right = n - left - 1;
    ret += Solve(type, left) * nCr[n - 1][left] * Solve(1, right);
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
  Initialize();
  for (int i = 0; i < kMaxN + 1; ++i)
  {
    CACHE[0][i] = -1;
    CACHE[1][i] = -1;
  }

  // Read Input
  int tc;
  cin >> tc;
  while (tc--)
  {
    cin >> N;

    // Solve
    if (N == 1)
    {
      cout << 1 << '\n';
    }
    else
    {
      cout << Solve(0, N) + Solve(1, N) << '\n';
    }
  }

  return 0;
}
