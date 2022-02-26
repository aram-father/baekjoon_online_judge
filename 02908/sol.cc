#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> neighbor_t;

const int kMaxN = 16;
const int kMaxCost = 1000000;

int N;
vector<vector<neighbor_t> > ADJ;
int CACHE[kMaxN][1 << kMaxN];

int Solve(const int city, const int visit)
{
  if (visit + 1 == (1 << N))
  {
    if (city == 0)
    {
      return 0;
    }
    else
    {
      for (const auto& neighbor : ADJ[city])
      {
        if (neighbor.first == 0)
        {
          return neighbor.second;
        }
      }

      return kMaxN * kMaxCost + 1;
    }
  }

  int& ret = CACHE[city][visit];
  if (ret != -1)
  {
    return ret;
  }

  ret = kMaxN * kMaxCost + 1;

  for (const auto& neighbor : ADJ[city])
  {
    int there = neighbor.first;
    int cost = neighbor.second;

    if (visit & (1 << there))
    {
      continue;
    }

    ret = min(ret, cost + Solve(there, visit | (1 << there)));
  }

  return ret;
}

int main(void)
{
  // Read inputs
  scanf(" %d", &N);
  ADJ.assign(N, vector<neighbor_t>());

  for (int u = 0; u < N; ++u)
  {
    for (int v = 0; v < N; ++v)
    {
      int cost;
      scanf(" %d", &cost);
      if (cost != 0)
      {
        ADJ[u].emplace_back(v, cost);
      }
    }
  }

  // Initialize cache
  for (int city = 0; city < kMaxN; ++city)
  {
    for (int visit = 0; visit < (1 << kMaxN); ++visit)
    {
      CACHE[city][visit] = -1;
    }
  }

  // Solve
  printf("%d\n", Solve(0, 1));

  return 0;
}
