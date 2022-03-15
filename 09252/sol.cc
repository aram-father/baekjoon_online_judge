#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;

string A;
string B;
int CACHE[kMaxN][kMaxN];

int GetLcsLength(const int i, const int j)
{
  if (i < 0 || j < 0)
  {
    return 0;
  }

  int& ret = CACHE[i][j];

  if (ret != -1)
  {
    return ret;
  }

  if (A[i] == B[j])
  {
    ret = GetLcsLength(i - 1, j - 1) + 1;
  }
  else
  {
    ret = max(GetLcsLength(i - 1, j), GetLcsLength(i, j - 1));
  }

  return ret;
}

string GetLcs(const int i, const int j)
{
  if (i < 0 || j < 0)
  {
    return "";
  }
  else if (A[i] == B[j])
  {
    return GetLcs(i - 1, j - 1) + A[i];
  }
  else if (GetLcsLength(i - 1, j) >= GetLcsLength(i, j - 1))
  {
    return GetLcs(i - 1, j);
  }
  else
  {
    return GetLcs(i, j - 1);
  }
}

int main(void)
{
  // Initialize
  for (int i = 0; i < kMaxN; ++i)
  {
    for (int j = 0; j < kMaxN; ++j)
    {
      CACHE[i][j] = -1;
    }
  }

  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read inputs
  cin >> A >> B;

  // Solve
  cout << GetLcsLength(A.size() - 1, B.size() - 1) << '\n';
  if (GetLcsLength(A.size() - 1, B.size() - 1))
  {
    cout << GetLcs(A.size() - 1, B.size() - 1) << '\n';
  }

  return 0;
}
