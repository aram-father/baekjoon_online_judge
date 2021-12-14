#include <iostream>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;

int N;
int ARR[kMaxN];
int INCR[kMaxN];
int DECR[kMaxN];

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;
  for (int i = 0; i < N; ++i)
  {
    cin >> ARR[i];
  }

  INCR[0] = 1;
  DECR[N - 1] = 1;

  for (int i = 1; i < N; ++i)
  {
    INCR[i] = 1;
    for (int j = 0; j < i; ++j)
    {
      if (ARR[j] < ARR[i])
      {
        INCR[i] = max(INCR[i], INCR[j] + 1);
      }
    }
  }

  for (int i = N - 2; i >= 0; --i)
  {
    DECR[i] = 1;
    for (int j = N - 1; j > i; --j)
    {
      if (ARR[i] > ARR[j])
      {
        DECR[i] = max(DECR[i], DECR[j] + 1);
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i)
  {
    ans = max(ans, INCR[i] + DECR[i] - 1);
  }

  cout << ans << '\n';

  return 0;
}
