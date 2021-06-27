#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int kMaxN = 100;
const int kMaxM = 100;

int N;
int M;
int COST[kMaxN + kMaxM + 2][kMaxN + kMaxM + 2];
int CAPA[kMaxN + kMaxM + 2][kMaxN + kMaxM + 2];
int FLOW[kMaxN + kMaxM + 2][kMaxN + kMaxM + 2];

int Spfa(vector<int>& prev)
{
  prev.assign(N + M + 2, -1);

  const int source = 0;
  const int sink = N + M + 2 - 1;

  vector<bool> queued(N + M + 2, false);
  vector<int> distance(N + M + 2, (N + M + 2) * 1000 + 1);

  queue<int> q;

  q.push(source);
  queued[source] = true;
  distance[source] = 0;

  while (!q.empty())
  {
    int here = q.front();
    q.pop();

    queued[here] = false;

    for (int there = 0; there < N + M + 2; ++there)
    {
      int residual = CAPA[here][there] - FLOW[here][there];
      if (residual > 0 && distance[there] > distance[here] + COST[here][there])
      {
        distance[there] = distance[here] + COST[here][there];
        prev[there] = here;
        if (!queued[there])
        {
          q.push(there);
          queued[there] = true;
        }
      }
    }
  }

  if (prev[sink] == -1)
  {
    return 0;
  }

  int flow = 100 * 100 + 1;
  int cur = sink;
  while (cur != source)
  {
    int residual = CAPA[prev[cur]][cur] - FLOW[prev[cur]][cur];
    flow = min(flow, residual);
    cur = prev[cur];
  }

  return flow;
}

int Solve(void)
{
  int ret = 0;

  const int source = 0;
  const int sink = N + M + 2 - 1;

  while (true)
  {
    vector<int> prev;

    int flow = Spfa(prev);

    if (flow == 0)
    {
      break;
    }

    int cur = sink;
    while (cur != source)
    {
      ret += COST[prev[cur]][cur] * flow;
      FLOW[prev[cur]][cur] += flow;
      FLOW[cur][prev[cur]] -= flow;
      cur = prev[cur];
    }
  }

  return ret;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> N >> M;

  const int source = 0;
  const int sink = N + M + 2 - 1;

  for (int it = 1; it < 1 + N; ++it)
  {
    int want;
    cin >> want;
    COST[source][it] = 0;
    CAPA[source][it] = want;
    FLOW[source][it] = 0;
    FLOW[it][source] = 0;
  }

  for (int it = 1 + N; it < 1 + N + M; ++it)
  {
    int have;
    cin >> have;
    COST[it][sink] = 0;
    CAPA[it][sink] = have;
    FLOW[it][sink] = 0;
    FLOW[sink][it] = 0;
  }

  for (int i = 1 + N; i < 1 + N + M; ++i)
  {
    for (int j = 1; j < 1 + N; ++j)
    {
      int cost;
      cin >> cost;
      COST[j][i] = cost;
      COST[i][j] = -cost;
      CAPA[j][i] = 100 * 100 + 1;
    }
  }

  cout << Solve() << "\n";

  return 0;
}
