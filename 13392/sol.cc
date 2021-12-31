#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 10000;

int N;
int S[kMaxN + 1];
int T[kMaxN + 1];
int CACHE[kMaxN + 1][10];

int Solve(const int screw_idx, const int left_turn)
{
  if (screw_idx > N)
  {
    return 0;
  }

  int& ret = CACHE[screw_idx][left_turn];
  if (ret != -1)
  {
    return ret;
  }

  int cur = (S[screw_idx] + left_turn) % 10;
  int lmove = (T[screw_idx] - cur < 0) ? T[screw_idx] - cur + 10 : T[screw_idx] - cur;
  int rmove = (cur - T[screw_idx] < 0) ? cur - T[screw_idx] + 10 : cur - T[screw_idx];

  ret = min(rmove + Solve(screw_idx + 1, left_turn), lmove + Solve(screw_idx + 1, (left_turn + lmove) % 10));

  return ret;
}

int main(void)
{
  // Initialize
  for (int i = 0; i < kMaxN + 1; ++i)
  {
    for (int j = 0; j < 10; ++j)
    {
      CACHE[i][j] = -1;
    }
  }

  // Read Inputs
  scanf(" %d", &N);
  for (int idx = 1; idx <= N; ++idx)
  {
    scanf(" %1d", &S[idx]);
  }
  for (int idx = 1; idx <= N; ++idx)
  {
    scanf(" %1d", &T[idx]);
  }

  // Solve
  printf("%d\n", Solve(1, 0));

  return 0;
}
