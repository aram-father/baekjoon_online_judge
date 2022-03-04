#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 100000;
const int kMaxCost = kMaxN * 5;

const int kCost[5][5] = { { 0, 2, 2, 2, 2 },
                          { kMaxCost, 1, 3, 4, 3 },
                          { kMaxCost, 3, 1, 3, 4 },
                          { kMaxCost, 4, 3, 1, 3 },
                          { kMaxCost, 3, 4, 3, 1 } };

vector<int> SEQUENCE;

int CACHE[kMaxN][5][5];

int Solve()
{
  CACHE[0][SEQUENCE[0]][0] = 2;
  CACHE[0][0][SEQUENCE[0]] = 2;

  for (size_t seq = 1; seq < SEQUENCE.size(); ++seq)
  {
    for (int lr = 0; lr < 25; ++lr)
    {
      const int l = lr / 5;
      const int r = lr % 5;

      if (SEQUENCE[seq] != l && SEQUENCE[seq] != r)
      {
        continue;
      }

      if (l == r)
      {
        continue;
      }

      for (int p = 0; p < 5; ++p)
      {
        if (SEQUENCE[seq] == l)
        {
          CACHE[seq][l][r] = min(CACHE[seq][l][r], CACHE[seq - 1][p][r] + kCost[p][l]);
        }
        else
        {
          CACHE[seq][l][r] = min(CACHE[seq][l][r], CACHE[seq - 1][l][p] + kCost[p][r]);
        }
      }
    }
  }

  int answer = kMaxCost;
  for (int left = 0; left < 5; ++left)
  {
    for (int right = 0; right < 5; ++right)
    {
      answer = min(answer, CACHE[SEQUENCE.size() - 1][left][right]);
    }
  }

  return answer;
}

int main(void)
{
  while (true)
  {
    int target;
    scanf(" %d", &target);

    if (target == 0)
    {
      break;
    }

    SEQUENCE.emplace_back(target);
  }

  for (int i = 0; i < kMaxN; ++i)
  {
    for (int j = 0; j < 5; ++j)
    {
      for (int k = 0; k < 5; ++k)
      {
        CACHE[i][j][k] = kMaxCost;
      }
    }
  }

  printf("%d\n", Solve());

  return 0;
}
