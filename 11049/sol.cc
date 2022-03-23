#include <cstdio>
#include <limits>
#include <utility>
#include <algorithm>

using namespace std;

const int kMaxN = 500;

int N;
pair<int, int> M[kMaxN];

int CACHE[kMaxN][kMaxN];

int main(void)
{
  // Read input
  scanf(" %d", &N);
  for (int it = 0; it < N; ++it)
  {
    scanf(" %d %d", &M[it].first, &M[it].second);
  }

  // Solve
  for (int s = N - 1; s >= 0; --s)
  {
    for (int e = s + 1; e < N; ++e)
    {
      CACHE[s][e] = numeric_limits<int>::max();
      for (int m = s; m < e; ++m)
      {
        CACHE[s][e] = min(CACHE[s][e], CACHE[s][m] + CACHE[m + 1][e] + M[s].first * M[m].second * M[e].second);
      }
    }
  }

  // Print answer
  printf("%d\n", CACHE[0][N - 1]);

  return 0;
}
