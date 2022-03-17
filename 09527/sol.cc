#include <iostream>
#include <cstdint>

using namespace std;

uint64_t A, B;

uint64_t Count1s(const uint64_t number)
{
  const uint64_t length = number + 1;

  uint64_t ret = 0;
  for (uint64_t period = 2; period / 2 < length; period *= 2)
  {
    ret += (length / period) * (period / 2);
    uint64_t remainder = length % period;
    if (remainder > 0 && remainder > period / 2)
    {
      ret += remainder - period / 2;
    }
  }

  return ret;
}

int main(void)
{
  // Read inputs
  cin >> A >> B;

  // Solve
  cout << Count1s(B) - Count1s(A - 1) << endl;

  return 0;
}
