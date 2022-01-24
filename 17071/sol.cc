#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;

const int kMaxN = 500000;

int SUBIN;
int BROTHER;

int VISIT[kMaxN + 1][2];

void Bfs()
{
  queue<pair<int, int> > q;

  VISIT[SUBIN][0] = 0;
  q.emplace(SUBIN, 0);

  while (!q.empty())
  {
    int here = q.front().first;
    int odd = q.front().second;
    q.pop();

    if (0 <= here - 1 && VISIT[here - 1][1 - odd] == -1)
    {
      VISIT[here - 1][1 - odd] = VISIT[here][odd] + 1;
      q.emplace(here - 1, 1 - odd);
    }

    if (here + 1 <= kMaxN && VISIT[here + 1][1 - odd] == -1)
    {
      VISIT[here + 1][1 - odd] = VISIT[here][odd] + 1;
      q.emplace(here + 1, 1 - odd);
    }

    if (here * 2 <= kMaxN && VISIT[here * 2][1 - odd] == -1)
    {
      VISIT[here * 2][1 - odd] = VISIT[here][odd] + 1;
      q.emplace(here * 2, 1 - odd);
    }
  }
}

int Solve()
{
  Bfs();

  for (int sec = 0;; ++sec)
  {
    BROTHER += sec;
    if (BROTHER > kMaxN)
    {
      return -1;
    }
    else if (VISIT[BROTHER][sec % 2] != -1 && VISIT[BROTHER][sec % 2] <= sec &&
             (sec - VISIT[BROTHER][sec % 2]) % 2 == 0)
    {
      return sec;
    }
  }
}

int main(void)
{
  // Initialize
  for (int i = 0; i < kMaxN + 1; ++i)
  {
    VISIT[i][0] = -1;
    VISIT[i][1] = -1;
  }

  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> SUBIN >> BROTHER;

  // Solve
  cout << Solve() << '\n';

  return 0;
}
