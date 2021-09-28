#include <iostream>
#include <vector>

using namespace std;

const size_t kMod = 10000003;
const size_t kMaxN = 100;
const size_t kMaxNumber = 100000;

size_t N;
vector<size_t> NUMBERS;
size_t DP[kMaxN][kMaxNumber + 1];

size_t GetGcd(size_t a, size_t b)
{
  if (a < b)
  {
    return GetGcd(b, a);
  }

  while (a % b)
  {
    size_t r = a % b;
    a = b;
    b = r;
  }

  return b;
}

size_t Solve(void)
{
  for (size_t i = 0; i < NUMBERS.size(); ++i)
  {
    DP[i][NUMBERS[i]] = 1;
  }

  for (size_t i = 1; i < NUMBERS.size(); ++i)
  {
    for (size_t j = 1; j <= kMaxNumber; ++j)
    {
      DP[i][j] += DP[i - 1][j];
      DP[i][j] %= kMod;
    }
    for (size_t k = 1; k <= kMaxNumber; ++k)
    {
      size_t g = GetGcd(NUMBERS[i], k);
      DP[i][g] += DP[i - 1][k];
      DP[i][g] %= kMod;
    }
  }

  return DP[NUMBERS.size() - 1][1] % kMod;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;
  NUMBERS.assign(N, 1);
  for (size_t it = 0; it < N; ++it)
  {
    cin >> NUMBERS[it];
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
