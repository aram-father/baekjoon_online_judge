#include <iostream>

using namespace std;

int32_t N, M;
int32_t NUMBER[2000];
uint8_t CACHE[2000][2000];

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> N;
  for (int it = 0; it < N; ++it)
  {
    cin >> NUMBER[it];
  }

  // DP
  for (int s = 0; s < N; ++s)
  {
    CACHE[s][s] = 1;
  }

  for (int s = N - 2; s >= 0; --s)
  {
    for (int e = s + 1; e < N; ++e)
    {
      if (s + 1 <= e - 1)
      {
        CACHE[s][e] = (CACHE[s + 1][e - 1] && NUMBER[s] == NUMBER[e]) ? 1 : 0;
      }
      else
      {
        CACHE[s][e] = (NUMBER[s] == NUMBER[e]) ? 1 : 0;
      }
    }
  }

  // Solve
  cin >> M;
  for (int it = 0; it < M; ++it)
  {
    int s, e;
    cin >> s >> e;
    cout << (int)CACHE[s - 1][e - 1] << '\n';
  }

  return 0;
}
