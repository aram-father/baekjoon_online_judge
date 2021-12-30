#include <iostream>
#include <string>

using namespace std;

const int kMaxN = 30;
const int kMaxK = 15 * 29;

const int kTrue = 1;
const int kFalse = 0;

int N;
int K;
int CACHE[kMaxN + 1][kMaxN + 1][kMaxN + 1][kMaxK + 1];

void InitializeCache()
{
  const size_t kSize = (kMaxN + 1) * (kMaxN + 1) * (kMaxN + 1) * (kMaxK + 1);
  int* const offset = &(CACHE[0][0][0][0]);
  for (size_t idx = 0; idx < kSize; ++idx)
  {
    offset[idx] = -1;
  }
}

bool IsPossible(const int na, const int nb, const int nc, const int k)
{
  if (na < 0 || nb < 0 || nc < 0 || k < 0)
  {
    return false;
  }

  if (na == 0 && nb == 0 && nc == 0 && k == 0)
  {
    return true;
  }

  int& ret = CACHE[na][nb][nc][k];
  if (ret != -1)
  {
    return (ret == kTrue);
  }

  ret = kFalse;

  if (IsPossible(na - 1, nb, nc, k))
  {
    ret = kTrue;
  }
  else if (IsPossible(na, nb - 1, nc, k - na))
  {
    ret = kTrue;
  }
  else if (IsPossible(na, nb, nc - 1, k - na - nb))
  {
    ret = kTrue;
  }

  return (ret == kTrue);
}

void Backtrack(const int na, const int nb, const int nc, const int k, string& str)
{
  if (na < 0 || nb < 0 || nc < 0 || k < 0)
  {
    return;
  }

  if (na == 0 && nb == 0 && nc == 0 && k == 0)
  {
    return;
  }

  if (IsPossible(na - 1, nb, nc, k))
  {
    Backtrack(na - 1, nb, nc, k, str);
    str += "A";
  }
  else if (IsPossible(na, nb - 1, nc, k - na))
  {
    Backtrack(na, nb - 1, nc, k - na, str);
    str += "B";
  }
  else if (IsPossible(na, nb, nc - 1, k - na - nb))
  {
    Backtrack(na, nb, nc - 1, k - na - nb, str);
    str += "C";
  }

  return;
}

string Solve()
{
  InitializeCache();

  for (int na = 0; na <= N; ++na)
  {
    for (int nb = 0; na + nb <= N; ++nb)
    {
      int nc = N - na - nb;

      if (nc >= 0 && IsPossible(na, nb, nc, K))
      {
        string ret = "";
        Backtrack(na, nb, nc, K, ret);
        return ret;
      }
    }
  }

  return string("-1");
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N >> K;

  // Solve
  cout << Solve() << '\n';

  return 0;
}
