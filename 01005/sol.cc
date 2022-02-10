#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 1000;

int T;
int N;
int K;
int DURATIONS[kMaxN + 1];
vector<vector<pair<int, int>>> ADJ;
int W;

void Dfs(const int v, vector<bool>& visit, vector<int>& topology)
{
  visit[v] = true;
  for (auto neighbor : ADJ[v])
  {
    if (!visit[neighbor.first])
    {
      Dfs(neighbor.first, visit, topology);
    }
  }

  topology.emplace_back(v);
}

int Solve(const int dst)
{
  vector<bool> visit(N + 1, false);
  vector<int> topology;

  Dfs(0, visit, topology);

  vector<int> dist(N + 1, 0);

  for (auto v = topology.rbegin(); v != topology.rend(); ++v)
  {
    int here = *v;
    for (auto neighbor : ADJ[here])
    {
      int there = neighbor.first;
      int cost = neighbor.second;

      if (dist[there] < dist[here] + cost)
      {
        dist[there] = dist[here] + cost;
      }
    }
  }

  return dist[dst];
}

int main(void)
{
  scanf(" %d", &T);
  while (T--)
  {
    scanf(" %d %d", &N, &K);
    for (int it = 1; it <= N; ++it)
    {
      scanf(" %d", &DURATIONS[it]);
    }

    ADJ.assign(N + 1, vector<pair<int, int>>());
    for (int it = 1; it <= N; ++it)
    {
      ADJ[0].emplace_back(it, 0);
    }

    for (int it = 0; it < K; ++it)
    {
      int src, dst;
      scanf(" %d %d", &src, &dst);
      ADJ[src].emplace_back(dst, DURATIONS[src]);
    }

    scanf(" %d", &W);

    printf("%d\n", Solve(W) + DURATIONS[W]);
  }

  return 0;
}
