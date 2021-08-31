#include <iostream>
#include <cstdint>

using namespace std;

const size_t kMaxN = 100;
const int64_t kMod = 1000000007;

int64_t CACHE[kMaxN + 1][kMaxN + 1][kMaxN + 1];

int64_t Solve(const int64_t n, const int64_t l, const int64_t r)
{
  CACHE[1][1][1] = 1;
  for (int64_t bldg = 2; bldg <= n; ++bldg)
  {
    for (int64_t left = 1; left <= bldg; ++left)
    {
      for (int64_t right = 1; left + right - 1 <= n; ++right)
      {
        CACHE[bldg][left][right] = CACHE[bldg - 1][left][right] * (bldg - 2);

        if (left >= 2)
        {
          CACHE[bldg][left][right] += CACHE[bldg - 1][left - 1][right];
        }
        if (right >= 2)
        {
          CACHE[bldg][left][right] += CACHE[bldg - 1][left][right - 1];
        }

        CACHE[bldg][left][right] %= kMod;
      }
    }
  }

  return CACHE[n][l][r];
}

int main(void)
{
  int64_t n, l, r;
  cin >> n >> l >> r;
  cout << Solve(n, l, r) << '\n';

  return 0;
}
