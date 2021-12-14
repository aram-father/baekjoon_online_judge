#include <iostream>
#include <limits>
#include <algorithm>

using namespace std;

const int kMaxK = 500;

int K;
int FILES[kMaxK];
int PSUMS[kMaxK];
int CACHE[kMaxK][kMaxK];

int Solve(const int s, const int e)
{
  if (s >= e)
  {
    return 0;
  }

  int& ret = CACHE[s][e];

  if (ret != -1)
  {
    return ret;
  }

  ret = numeric_limits<int>::max();
  for (int m = s; m <= e; ++m)
  {
    ret = min(ret, Solve(s, m) + Solve(m + 1, e) + PSUMS[e] - PSUMS[s] + FILES[s]);
  }

  return ret;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Testcase
  int testcase;
  cin >> testcase;

  while (testcase--)
  {
    // Read Input
    cin >> K;
    for (int i = 0; i < K; ++i)
    {
      cin >> FILES[i];
    }

    // Initialize
    int psum = 0;
    for (int i = 0; i < kMaxK; ++i)
    {
      psum += FILES[i];
      PSUMS[i] = psum;
      for (int j = i; j < kMaxK; ++j)
      {
        CACHE[i][j] = -1;
      }
    }

    cout << Solve(0, K - 1) << '\n';
  }

  return 0;
}
