#include <iostream>
#include <cstdint>
#include <cstdio>

using namespace std;

const int kMaxN = 100;
const int64_t kMod = 1000000000;

int N;
int64_t CACHE[kMaxN + 1][10][1 << 10];

int main(void)
{
  // Read input
  scanf(" %d", &N);

  // Initialize cache
  for (int ending_digit = 1; ending_digit < 10; ++ending_digit)
  {
    CACHE[1][ending_digit][1 << ending_digit] = 1;
  }

  // Solve
  for (int num_of_digits = 2; num_of_digits <= N; ++num_of_digits)
  {
    for (int ending_digit = 0; ending_digit < 10; ++ending_digit)
    {
      for (int prev_used = 0; prev_used < (1 << 10); ++prev_used)
      {
        int next_used = prev_used | (1 << ending_digit);

        if (ending_digit != 0)
        {
          CACHE[num_of_digits][ending_digit][next_used] += CACHE[num_of_digits - 1][ending_digit - 1][prev_used];
          CACHE[num_of_digits][ending_digit][next_used] %= kMod;
        }

        if (ending_digit != 9)
        {
          CACHE[num_of_digits][ending_digit][next_used] += CACHE[num_of_digits - 1][ending_digit + 1][prev_used];
          CACHE[num_of_digits][ending_digit][next_used] %= kMod;
        }
      }
    }
  }
  int64_t answer = 0;
  for (int ending_digit = 0; ending_digit < 10; ++ending_digit)
  {
    answer = (answer + CACHE[N][ending_digit][(1 << 10) - 1]) % kMod;
  }

  // Print answer
  printf("%ld\n", answer);

  return 0;
}
