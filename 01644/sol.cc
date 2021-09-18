#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

uint64_t N;
vector<bool> IS_PRIME;
vector<uint64_t> PSUM;

void DoSieve(void)
{
  for (uint64_t i = 2; i * i <= N; ++i)
  {
    if (!IS_PRIME[i])
    {
      continue;
    }

    for (uint64_t j = i * i; j <= N; j += i)
    {
      IS_PRIME[j] = false;
    }
  }

  PSUM.emplace_back(0);
  for (uint64_t i = 2; i <= N; ++i)
  {
    if (IS_PRIME[i])
    {
      PSUM.emplace_back(i + PSUM.back());
    }
  }
}

uint64_t Solve(void)
{
  uint64_t ans = 0;

  uint64_t lptr = 1;
  uint64_t rptr = 1;

  while (lptr <= rptr && rptr < PSUM.size())
  {
    uint64_t sum = PSUM[rptr] - PSUM[lptr - 1];

    if (sum == N)
    {
      ++ans;
    }

    if (sum >= N)
    {
      ++lptr;
    }
    else
    {
      ++rptr;
    }
  }

  return ans;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;

  // Sieve
  IS_PRIME.assign(N + 1, true);
  DoSieve();

  // Solve
  cout << Solve() << '\n';

  return 0;
}
