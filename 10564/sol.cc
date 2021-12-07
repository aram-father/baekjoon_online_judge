#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int kMaxN = 5000;
const int kTrue = 1;
const int kFalse = 2;
const int kUndefined = 0;

int N, M;
vector<int> SCORES;
int CACHE[kMaxN + 1][kMaxN + 1];

int Solve(const int n, const int s)
{
  int& ret = CACHE[n][s];
  if (ret != kUndefined)
  {
    return ret;
  }

  ret = kFalse;
  for (const auto& score : SCORES)
  {
    if (n >= s && s >= score && n - s >= s - score)
    {
      if (Solve(n - s, s - score) == kTrue)
      {
        ret = kTrue;
        break;
      }
    }
  }

  return ret;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int testcase;
  cin >> testcase;

  while (testcase--)
  {
    memset(CACHE, 0, sizeof(CACHE));

    cin >> N >> M;
    SCORES.assign(M, 0);
    for (auto& score : SCORES)
    {
      cin >> score;
    }

    CACHE[0][0] = kTrue;

    int ans = -1;
    for (int s = N; s >= 0; --s)
    {
      if (Solve(N, s) == kTrue)
      {
        ans = s;
        break;
      }
    }

    cout << ans << '\n';
  }

  return 0;
}
