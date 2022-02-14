#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

const int kMaxN = 2500;

int N;
string S;
int PARTITIONS[kMaxN + 1];
int PALINDROME[kMaxN + 1][kMaxN + 1];

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> S;
  N = (int)S.size();
  S = "-" + S;

  // Solve palindrome table
  for (int s = N; s >= 0; --s)
  {
    for (int e = s; e <= N; ++e)
    {
      if (s == e)
      {
        PALINDROME[s][e] = 1;
      }
      else if (S[s] == S[e] && (s + 1 > e - 1 || PALINDROME[s + 1][e - 1] == 1))
      {
        PALINDROME[s][e] = 1;
      }
      else
      {
        PALINDROME[s][e] = 0;
      }
    }
  }

  // Solve
  PARTITIONS[0] = 0;
  for (int pos = 1; pos <= N; ++pos)
  {
    PARTITIONS[pos] = kMaxN * kMaxN;
    for (int prev = pos - 1; prev >= 0; --prev)
    {
      if (PALINDROME[prev + 1][pos])
      {
        PARTITIONS[pos] = min(PARTITIONS[pos], PARTITIONS[prev] + 1);
      }
    }
  }

  cout << PARTITIONS[N] << '\n';

  return 0;
}
