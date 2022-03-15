#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxN = 100;
const int kMaxM = 10000000;
const int kMaxC = 100;

int N;
int M;
int CACHE[kMaxN][kMaxC * kMaxN + 1];

int MEMORY[kMaxN];
int ACTIVATE[kMaxN];

int Solve()
{
  for (int act = 0; act <= kMaxC * N; ++act)
  {
    if (act < ACTIVATE[0])
    {
      CACHE[0][act] = 0;
    }
    else
    {
      CACHE[0][act] = MEMORY[0];
    }
  }

  for (int idx = 1; idx < N; ++idx)
  {
    for (int act = 0; act <= kMaxC * N; ++act)
    {
      if (act < ACTIVATE[idx])
      {
        CACHE[idx][act] = CACHE[idx - 1][act];
      }
      else
      {
        CACHE[idx][act] = max(CACHE[idx - 1][act], CACHE[idx - 1][act - ACTIVATE[idx]] + MEMORY[idx]);
      }
    }
  }

  for (int act = 0; act <= kMaxC * N; ++act)
  {
    if (CACHE[N - 1][act] >= M)
    {
      return act;
    }
  }

  return -1;
}

int main(void)
{
  // Read input
  scanf(" %d %d", &N, &M);
  for (int it = 0; it < N; ++it)
  {
    scanf(" %d", &MEMORY[it]);
  }
  for (int it = 0; it < N; ++it)
  {
    scanf(" %d", &ACTIVATE[it]);
  }

  // Solve
  printf("%d\n", Solve());

  return 0;
}
