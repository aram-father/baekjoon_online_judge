#include <iostream>
#include <cstdint>

using namespace std;

const size_t kMaxN = 10;
const int64_t kOne = 1;

int64_t N;
int64_t M;
int64_t PRIMES[kMaxN];

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin >> N >> M;
  for (int64_t it = 0; it < N; ++it)
  {
    cin >> PRIMES[it];
  }

  // Solve
  int64_t num_of_mults = 0;
  for (int64_t mask = 1; mask < (kOne << N); ++mask)
  {
    int64_t odd = 0;
    int64_t mul = 1;
    for (int64_t bit = 0; bit < N; ++bit)
    {
      if (mask & (kOne << bit))
      {
        odd = 1 - odd;
        mul *= PRIMES[bit];
      }
    }

    num_of_mults += odd ? M / mul : -M / mul;
  }

  cout << num_of_mults << '\n';

  return 0;
}
