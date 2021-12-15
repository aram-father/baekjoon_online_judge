#include <iostream>
#include <cstdint>
#include <vector>

using namespace std;

const int kSqrtMaxN = 1000000;

int64_t N;
bool IS_COMP[kSqrtMaxN + 1];

void DoSieve(void)
{
  for (int64_t i = 2; i <= kSqrtMaxN; ++i)
  {
    if (!IS_COMP[i])
    {
      for (int64_t j = i * i; j <= kSqrtMaxN; j += i)
      {
        IS_COMP[j] = true;
      }
    }
  }
}

int64_t Solve(void)
{
  vector<int64_t> factors;

  int64_t n = N;
  for (int64_t i = 2; i * i <= N; ++i)
  {
    if (n % i == 0 && !IS_COMP[i])
    {
      factors.emplace_back(i);

      while (n % i == 0)
      {
        n /= i;
      }
    }
  }

  if (n != 1)
  {
    factors.emplace_back(n);
  }

  int64_t sum = 0;

  for (int mask = 1; mask < (1 << factors.size()); ++mask)
  {
    int64_t lcm = 1;
    int64_t number_of_sets = 0;

    for (int bit = 0; (1 << bit) <= mask; ++bit)
    {
      if (mask & (1 << bit))
      {
        lcm *= factors[bit];
        ++number_of_sets;
      }
    }

    if (number_of_sets % 2)
    {
      sum += N / lcm;
    }
    else
    {
      sum -= N / lcm;
    }
  }

  return N - sum;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;

  // Solve
  DoSieve();
  cout << Solve() << '\n';

  return 0;
}
