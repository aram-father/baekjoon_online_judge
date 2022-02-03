#include <cstdio>

using namespace std;

const int kMaxM = 200000;
const int kMaxN = 500000;
const int kMaxExp = 18;  // 2^19 -1 > 500000

int CACHE[kMaxExp + 1][kMaxM + 1];

int M;
int Q;

int Solve(const int n, const int x)
{
  int ret = x;
  for (int bitpos = 0; bitpos <= kMaxExp; ++bitpos)
  {
    if (n & (1 << bitpos))
    {
      ret = CACHE[bitpos][ret];
    }
  }

  return ret;
}

int main(void)
{
  // Read inputs
  scanf(" %d", &M);
  for (int it = 1; it <= M; ++it)
  {
    scanf(" %d", &CACHE[0][it]);
  }

  // DP
  for (int e = 1; e <= kMaxExp; ++e)
  {
    for (int x = 1; x <= kMaxM; ++x)
    {
      CACHE[e][x] = CACHE[e - 1][CACHE[e - 1][x]];
    }
  }

  // Process queries
  scanf(" %d", &Q);
  for (int it = 0; it < Q; ++it)
  {
    int n, x;
    scanf(" %d %d", &n, &x);
    printf("%d\n", Solve(n, x));
  }

  return 0;
}
