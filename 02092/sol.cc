#include <iostream>
#include <algorithm>

using namespace std;

const size_t kMod = 1000000;
const size_t kMaxA = 4000;
const size_t kMaxT = 200;

size_t T, A, S, B;

size_t CNT[kMaxT + 1];
size_t CACHE[kMaxT + 1][kMaxA + 1];

size_t Solve(void)
{
  CACHE[0][0] = 1;

  for (size_t t = 1; t <= T; ++t)
  {
    for (size_t k = 0; k <= A; ++k)
    {
      for (size_t num_of_ts = 0; num_of_ts <= CNT[t] && k >= num_of_ts; ++num_of_ts)
      {
        CACHE[t][k] = (CACHE[t][k] + CACHE[t - 1][k - num_of_ts]) % kMod;
      }
    }
  }

  size_t ret = 0;
  for (size_t k = S; k <= B; ++k)
  {
    ret = (ret + CACHE[T][k]) % kMod;
  }

  return ret;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  cin >> T >> A >> S >> B;
  for (size_t it = 0; it < A; ++it)
  {
    size_t number;
    cin >> number;
    ++CNT[number];
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
