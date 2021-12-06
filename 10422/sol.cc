#include <iostream>
#include <cstdint>

using namespace std;

const int64_t kMod = 1000000007;
int64_t CACHE[5000 + 1];

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Solve all
  CACHE[0] = 1;
  CACHE[2] = 1;
  for (int64_t n = 4; n <= 5000; n += 2)
  {
    for (int64_t closing = 1; closing <= n; closing += 2)
    {
      CACHE[n] += CACHE[closing - 1] * CACHE[n - closing - 1];
      CACHE[n] %= kMod;
    }
  }

  int64_t tc;
  cin >> tc;

  while (tc--)
  {
    int64_t n;
    cin >> n;
    cout << CACHE[n] << '\n';
  }

  return 0;
}
