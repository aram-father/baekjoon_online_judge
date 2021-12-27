#include <iostream>
#include <string>

using namespace std;

const int kMaxN = 50;
const int kA = 0;
const int kB = 1;
const int kC = 2;
const int kTrue = 1;
const int kFalse = 2;

int CACHE[kMaxN + 1][kMaxN + 1][kMaxN + 1][kC + 1][kC + 1];

int Solve(const int na, const int nb, const int nc, const int prev, const int prev_prev)
{
  int& ret = CACHE[na][nb][nc][prev][prev_prev];
  if (ret != 0)
  {
    return ret;
  }

  if (na == 0 && nb == 0 && nc == 0)
  {
    ret = kTrue;
  }
  else if (na > 0 && Solve(na - 1, nb, nc, kA, prev) == kTrue)
  {
    ret = kTrue;
  }
  else if (nb > 0 && prev != kB && Solve(na, nb - 1, nc, kB, prev) == kTrue)
  {
    ret = kTrue;
  }
  else if (nc > 0 && prev != kC && prev_prev != kC && Solve(na, nb, nc - 1, kC, prev) == kTrue)
  {
    ret = kTrue;
  }
  else
  {
    ret = kFalse;
  }

  return ret;
}

void Backtrack(const int na, const int nb, const int nc, const int prev, const int prev_prev)
{
  if (na == 0 && nb == 0 && nc == 0)
  {
    return;
  }
  else if (na > 0 && Solve(na - 1, nb, nc, kA, prev) == kTrue)
  {
    cout << 'A';
    Backtrack(na - 1, nb, nc, kA, prev);
  }
  else if (nb > 0 && prev != kB && Solve(na, nb - 1, nc, kB, prev) == kTrue)
  {
    cout << 'B';
    Backtrack(na, nb - 1, nc, kB, prev);
  }
  else if (nc > 0 && prev != kC && prev_prev != kC && Solve(na, nb, nc - 1, kC, prev) == kTrue)
  {
    cout << 'C';
    Backtrack(na, nb, nc - 1, kC, prev);
  }
}

string S;
int NA;
int NB;
int NC;

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  cin >> S;
  for (const auto& ch : S)
  {
    switch (ch)
    {
      case 'A': {
        ++NA;
      }
      break;
      case 'B': {
        ++NB;
      }
      break;
      case 'C': {
        ++NC;
      }
      break;
    }
  }

  // Solve
  if (Solve(NA, NB, NC, kA, kA) == kFalse)
  {
    cout << "-1\n";
  }
  else
  {
    Backtrack(NA, NB, NC, kA, kA);
    cout << '\n';
  }

  return 0;
}
