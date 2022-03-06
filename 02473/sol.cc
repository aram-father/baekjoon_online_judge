#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <limits>

using namespace std;

inline int64_t ABS(const int64_t x)
{
  return x >= 0 ? x : -x;
}

const int kMaxN = 5000;
const int64_t kMaxAcidity = numeric_limits<int64_t>::max();

int N;
int64_t ACIDITY[kMaxN];

void Solve()
{
  sort(ACIDITY, ACIDITY + N);

  int64_t min_acidity = kMaxAcidity;
  int64_t l1, l2, l3;

  for (int a = 0; a < N; ++a)
  {
    int lo = a + 1;
    int hi = N - 1;

    while (lo < hi)
    {
      int64_t sum = ACIDITY[a] + ACIDITY[lo] + ACIDITY[hi];
      if (ABS(sum) < min_acidity)
      {
        min_acidity = ABS(sum);
        l1 = ACIDITY[a];
        l2 = ACIDITY[lo];
        l3 = ACIDITY[hi];
      }

      if (sum < 0)
      {
        ++lo;
      }
      else
      {
        --hi;
      }
    }
  }

  printf("%ld %ld %ld\n", l1, l2, l3);
}

int main(void)
{
  scanf(" %d", &N);
  for (int it = 0; it < N; ++it)
  {
    scanf(" %ld", &ACIDITY[it]);
  }

  Solve();

  return 0;
}
