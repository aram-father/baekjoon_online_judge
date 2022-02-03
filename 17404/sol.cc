#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;
const int kR = 0;
const int kG = 1;
const int kB = 2;

int N;
int COST[kMaxN][3];
int CACHE[kMaxN][3][3];

int main(void)
{
  // Initialize
  for (int i = 0; i < kMaxN; ++i)
  {
    for (int first = 0; first < 3; ++first)
    {
      for (int last = 0; last < 3; ++last)
      {
        CACHE[i][first][last] = kMaxN * kMaxN + 1;
      }
    }
  }

  // Read Input
  scanf(" %d", &N);
  for (int i = 0; i < N; ++i)
  {
    scanf(" %d %d %d", &COST[i][kR], &COST[i][kG], &COST[i][kB]);
  }

  // Base case
  for (int first = 0; first < 3; ++first)
  {
    for (int last = 0; last < 3; ++last)
    {
      if (first != last)
      {
        CACHE[1][first][last] = COST[0][first] + COST[1][last];
      }
    }
  }

  // Dp
  for (int i = 2; i < N; ++i)
  {
    for (int first = 0; first < 3; ++first)
    {
      for (int last = 0; last < 3; ++last)
      {
        int& target = CACHE[i][first][last];

        if (last == kR)
        {
          target = min(target, CACHE[i - 1][first][kG] + COST[i][kR]);
          target = min(target, CACHE[i - 1][first][kB] + COST[i][kR]);
        }
        if (last == kG)
        {
          target = min(target, CACHE[i - 1][first][kR] + COST[i][kG]);
          target = min(target, CACHE[i - 1][first][kB] + COST[i][kG]);
        }
        if (last == kB)
        {
          target = min(target, CACHE[i - 1][first][kR] + COST[i][kB]);
          target = min(target, CACHE[i - 1][first][kG] + COST[i][kB]);
        }
      }
    }
  }

  // Solve
  int ans = kMaxN * kMaxN + 1;
  for (int first = 0; first < 3; ++first)
  {
    for (int last = 0; last < 3; ++last)
    {
      if (first != last)
      {
        ans = min(ans, CACHE[N - 1][first][last]);
      }
    }
  }

  printf("%d\n", ans);

  return 0;
}
