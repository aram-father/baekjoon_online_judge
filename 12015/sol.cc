#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<int> CACHE;

int main(void)
{
  scanf(" %d", &N);
  for (int it = 0; it < N; ++it)
  {
    int number;
    scanf(" %d", &number);

    auto l = lower_bound(CACHE.begin(), CACHE.end(), number);
    if (l == CACHE.end())
    {
      CACHE.emplace_back(number);
    }
    else
    {
      *l = number;
    }
  }

  printf("%d\n", (int)CACHE.size());

  return 0;
}
