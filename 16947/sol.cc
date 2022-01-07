#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int kMaxN = 3000;

int N;
vector<pair<int, int> > ADJ[kMaxN + 1];
bool VISIT[kMaxN + 1];
int PARENT[kMaxN + 1];
vector<int> CYCLE;

int ClearCycleEdges(const int u)
{
  VISIT[u] = true;
  for (auto& neighbor : ADJ[u])
  {
    const int v = neighbor.second;
    if (PARENT[u] == v)
    {
      continue;
    }
    else if (VISIT[v])
    {
      int src = u;

      while (true)
      {
        CYCLE.emplace_back(src);
        if (src == v)
        {
          break;
        }
        else
        {
          src = PARENT[src];
        }
      }

      return v;
    }
    else
    {
      PARENT[v] = u;
      int ret = ClearCycleEdges(v);
      if (ret != -1)
      {
        return ret;
      }
    }
  }

  return -1;
}

void Dijkstra(void)
{
  vector<int> dist(N + 1, 2 * N);
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

  for (auto v : CYCLE)
  {
    dist[v] = 0;
    pq.emplace(dist[v], v);
  }

  while (!pq.empty())
  {
    int cost = pq.top().first;
    int here = pq.top().second;
    pq.pop();

    if (dist[here] < cost)
    {
      continue;
    }

    for (const auto& neighbor : ADJ[here])
    {
      int weight = neighbor.first;
      int there = neighbor.second;

      if (dist[there] > weight + dist[here])
      {
        dist[there] = weight + dist[here];
        pq.emplace(dist[there], there);
      }
    }
  }

  for (int idx = 1; idx <= N; ++idx)
  {
    cout << dist[idx] << ' ';
  }
  cout << '\n';
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;
  for (int i = 0; i < N; ++i)
  {
    int src, dst;
    cin >> src >> dst;
    ADJ[src].emplace_back(1, dst);
    ADJ[dst].emplace_back(1, src);
  }

  // Solve
  ClearCycleEdges(1);
  Dijkstra();

  return 0;
}
