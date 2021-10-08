#include <iostream>
#include <cstdint>

using namespace std;

uint64_t kMod = 1000000000;
uint64_t N;

uint64_t Solve(void)
{
  if (N == 1)
  {
    return 0;
  }
  else if (N == 2)
  {
    return 1;
  }

  uint64_t pp = 0;
  uint64_t p = 1;

  uint64_t ans = 0;
  for (uint64_t it = 3; it <= N; ++it)
  {
    ans = ((it - 1) * ((p + pp) % kMod)) % kMod;
    pp = p;
    p = ans;
  }

  return ans;
}

int main(void)
{
  cin >> N;
  cout << Solve() << '\n';

  return 0;
}
