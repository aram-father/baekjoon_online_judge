#include <iostream>
#include <cstdint>
#include <algorithm>

using namespace std;

int64_t Solve(const int64_t n, const int64_t k, int64_t begin, int64_t end)
{
  // Find lower_bound
  while (begin < end)
  {
    int64_t mid = (begin + end) / 2;

    int64_t lesser = 0;
    for (int64_t div = 1; div <= n; ++div)
    {
      lesser += min(mid, div * n) / div;
    }

    if (lesser < k)
    {
      begin = mid + 1;
    }
    else
    {
      end = mid;
    }
  }

  return end;
}

int main(void)
{
  int64_t n, k;
  cin >> n >> k;
  cout << Solve(n, k, 1, n * n) << '\n';
}
