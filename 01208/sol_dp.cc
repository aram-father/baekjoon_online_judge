#include <iostream>
#include <cstdint>

using namespace std;

static const int kMaxN = 40;
static const int kMaxI = 100000;
static const int kMaxSum = kMaxN * kMaxI;

inline int Sum2Idx(const int sum)
{
  return sum + kMaxSum;
}

int NUMS[kMaxN];
uint64_t CACHE[2][2 * kMaxSum + 1];

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  int N, S;
  cin >> N >> S;

  for (int it = 0; it < N; ++it)
  {
    cin >> NUMS[it];
  }

  // Solve
  CACHE[0][Sum2Idx(0)] += 1;
  CACHE[0][Sum2Idx(NUMS[0])] += 1;
  for (int i = 1; i < N; ++i)
  {
    for (int s = -N * kMaxI; s <= N * kMaxI; ++s)
    {
      CACHE[i % 2][Sum2Idx(s)] = CACHE[(i - 1) % 2][Sum2Idx(s)];
      if (-N * kMaxI <= s - NUMS[i] && s - NUMS[i] <= N * kMaxI)
      {
        CACHE[i % 2][Sum2Idx(s)] += CACHE[(i - 1) % 2][Sum2Idx(s - NUMS[i])];
      }
    }
  }

  // Print answer
  cout << CACHE[(N - 1) % 2][Sum2Idx(S)] - (S == 0 ? 1 : 0) << '\n';

  return 0;
}
