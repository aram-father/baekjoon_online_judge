#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 10000;
const int kNumOfDigits = 10;

int SRC[kMaxN + 1];
int DST[kMaxN + 1];

int N;
int CACHE[kMaxN + 1][kNumOfDigits];

void Initialize()
{
  for (int i = 0; i < kMaxN + 1; ++i)
  {
    for (int j = 0; j < kNumOfDigits; ++j)
    {
      CACHE[i][j] = -1;
    }
  }
}

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

  int current = (SRC[screw_idx] + left_turn) % kNumOfDigits;
  int target = DST[screw_idx];

  int lmove = ((target - current) + kNumOfDigits) % kNumOfDigits;
  int rmove = ((current - target) + kNumOfDigits) % kNumOfDigits;

  ret = min(lmove + Solve(screw_idx + 1, (left_turn + lmove) % kNumOfDigits), rmove + Solve(screw_idx + 1, left_turn));

  return ret;
}

void Backtrack(const int screw_idx, const int left_turn)
{
  if (screw_idx > N)
  {
    return;
  }

  int current = (SRC[screw_idx] + left_turn) % kNumOfDigits;
  int target = DST[screw_idx];

  int lmove = ((target - current) + kNumOfDigits) % kNumOfDigits;
  int rmove = ((current - target) + kNumOfDigits) % kNumOfDigits;

  int left_chosen = lmove + Solve(screw_idx + 1, (left_turn + lmove) % kNumOfDigits);
  int right_chosen = rmove + Solve(screw_idx + 1, left_turn);

  if (left_chosen < right_chosen)
  {
    printf("%d %d\n", screw_idx, lmove);
    Backtrack(screw_idx + 1, (left_turn + lmove) % kNumOfDigits);
  }
  else
  {
    printf("%d %d\n", screw_idx, -rmove);
    Backtrack(screw_idx + 1, left_turn);
  }

  return;
}

int main(void)
{
  // Read Inputs
  scanf(" %d", &N);
  for (int i = 1; i <= N; ++i)
  {
    scanf(" %1d", &SRC[i]);
  }
  for (int i = 1; i <= N; ++i)
  {
    scanf(" %1d", &DST[i]);
  }

  // Initialize
  Initialize();

  // Print total movements
  printf("%d\n", Solve(1, 0));

  // Print backtracking
  Backtrack(1, 0);

  return 0;
}
