#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

int N;
int V[1000000 + 1];
int P[1000000 + 1];

void Bfs(const int start)
{
  V[start] = 1;
  P[start] = -1;

  queue<int> q;
  q.emplace(start);

  while (!q.empty())
  {
    int here = q.front();
    q.pop();

    if (here == 1)
    {
      break;
    }

    if (here % 3 == 0 && !V[here / 3])
    {
      V[here / 3] = 1;
      P[here / 3] = here;
      q.emplace(here / 3);
    }

    if (here % 2 == 0 && !V[here / 2])
    {
      V[here / 2] = 1;
      P[here / 2] = here;
      q.emplace(here / 2);
    }

    if (here - 1 > 0 && !V[here - 1])
    {
      V[here - 1] = 1;
      P[here - 1] = here;
      q.emplace(here - 1);
    }
  }
}

vector<int> path;

int main(void)
{
  scanf(" %d", &N);
  Bfs(N);

  int n = 1;
  while (P[n] != -1)
  {
    path.emplace_back(n);
    n = P[n];
  }

  printf("%d\n%d ", (int)path.size(), N);
  for (auto r = path.rbegin(); r != path.rend(); ++r)
  {
    printf("%d ", *r);
  }
  printf("\n");

  return 0;
}
