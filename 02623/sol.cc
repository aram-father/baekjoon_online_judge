#include <cstdio>
#include <vector>

using namespace std;

int N;
int M;
vector<bool> V;
vector<bool> F;
vector<vector<int> > G;

bool DoDfs(int here, vector<int>& topology)
{
  V[here] = true;
  for (const auto& there : G[here])
  {
    if (!V[there])
    {
      if (!DoDfs(there, topology))
      {
        return false;
      }
    }
    else if (!F[there])
    {
      return false;
    }
  }

  topology.emplace_back(here);
  F[here] = true;
  return true;
}

void Solve()
{
  vector<int> answer;
  for (int singer = 1; singer <= N; ++singer)
  {
    if (!V[singer] && !DoDfs(singer, answer))
    {
      printf("%d\n", 0);
    }
  }

  for (auto it = answer.rbegin(); it != answer.rend(); ++it)
  {
    printf("%d\n", *it);
  }

  return;
}

int main(void)
{
  // Read input
  scanf(" %d %d", &N, &M);
  V.assign(N + 1, false);
  F.assign(N + 1, false);
  G.assign(N + 1, vector<int>());
  for (int pd = 0; pd < M; ++pd)
  {
    int num_of_singers;
    int predecessor;
    int successor;
    scanf(" %d %d", &num_of_singers, &predecessor);

    for (int singer = 1; singer < num_of_singers; ++singer)
    {
      scanf(" %d", &successor);
      G[predecessor].emplace_back(successor);
      predecessor = successor;
    }
  }

  // Solve
  Solve();

  return 0;
}
