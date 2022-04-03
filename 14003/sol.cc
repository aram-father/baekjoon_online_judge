#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 1000000;

int N;
int A[kMaxN];
int P[kMaxN];

vector<int> CACHE;
vector<int> LIS;

int main(void)
{
  // Read input
  scanf(" %d", &N);
  for (int i = 0; i < N; ++i)
  {
    scanf(" %d", &A[i]);
  }

  // Get length
  for (int i = 0; i < N; ++i)
  {
    auto it = lower_bound(CACHE.begin(), CACHE.end(), A[i]);
    if (it == CACHE.end())
    {
      CACHE.emplace_back(A[i]);
      P[i] = (int)CACHE.size() - 1;
    }
    else
    {
      *it = A[i];
      P[i] = (int)(it - CACHE.begin());
    }
  }

  // Print answer
  printf("%d\n", (int)CACHE.size());

  int target = (int)CACHE.size() - 1;
  for (int i = N - 1; i >= 0 && target >= 0; --i)
  {
    if (P[i] == target)
    {
      LIS.emplace_back(A[i]);
      --target;
    }
  }

  for (auto r = LIS.rbegin(); r != LIS.rend(); ++r)
  {
    printf("%d ", *r);
  }
  printf("\n");

  return 0;
}
