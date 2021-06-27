#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxN = 400;
const int kMaxM = 400;
const int kMaxCapa = 400 + 400 + 1;
const int kMaxDist = (400 + 400 + 2) * 10000 + 1;

int N;
int M;
int COST[kMaxN + kMaxM + 2][kMaxN + kMaxM + 2];
int CAPA[kMaxN + kMaxM + 2][kMaxN + kMaxM + 2];
int FLOW[kMaxN + kMaxM + 2][kMaxN + kMaxM + 2];
vector<vector<int> > ADJACENT_LIST;

int Spfa(vector<int>& prev)
{
  const int source = 0;
  const int sink = N + M + 2 - 1;

  prev.assign(N + M + 2, -1);

  vector<bool> queued(N + M + 2, false);
  vector<int> distance(N + M + 2, kMaxDist);

  queue<int> q;

  q.push(source);
  queued[source] = true;
  distance[source] = 0;

  while (!q.empty())
  {
    int here = q.front();
    q.pop();

    queued[here] = false;

    for (const auto& there : ADJACENT_LIST[here])
    {
      int residual = CAPA[here][there] - FLOW[here][there];
      if (residual > 0 && distance[there] > distance[here] + COST[here][there])
      {
        distance[there] = distance[here] + COST[here][there];
        prev[there] = here;
        if (!queued[there])
        {
          queued[there] = true;
          q.push(there);
        }
      }
    }
  }

  if (prev[sink] == -1)
  {
    return 0;
  }

  int flow = kMaxCapa;
  int current = sink;
  while (current != source)
  {
    int residual = CAPA[prev[current]][current] - FLOW[prev[current]][current];
    flow = min(flow, residual);
    current = prev[current];
  }

  return flow;
}

pair<int, int> Solve(void)
{
  const int source = 0;
  const int sink = N + M + 2 - 1;

  pair<int, int> ret{ 0, 0 };

  while (true)
  {
    vector<int> prev;
    const int flow = Spfa(prev);

    if (flow == 0)
    {
      break;
    }

    int current = sink;
    while (current != source)
    {
      ret.second += flow * COST[prev[current]][current];
      FLOW[prev[current]][current] += flow;
      FLOW[current][prev[current]] -= flow;

      current = prev[current];
    }

    ret.first += flow;
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

  ADJACENT_LIST.assign(N + M + 2, vector<int>());

  for (int emply = 1; emply < 1 + N; ++emply)
  {
    COST[source][emply] = 0;
    COST[emply][source] = 0;
    CAPA[source][emply] = 1;
    FLOW[source][emply] = 0;
    FLOW[emply][source] = 0;
    ADJACENT_LIST[source].push_back(emply);
    ADJACENT_LIST[emply].push_back(source);

    int num_of_works;
    cin >> num_of_works;
    for (int it = 0; it < num_of_works; ++it)
    {
      int work, pay;
      cin >> work >> pay;

      COST[emply][1 + N + work - 1] = -pay;
      COST[1 + N + work - 1][emply] = pay;
      CAPA[emply][1 + N + work - 1] = kMaxCapa;
      FLOW[emply][1 + N + work - 1] = 0;
      FLOW[1 + N + work - 1][emply] = 0;
      ADJACENT_LIST[emply].push_back(1 + N + work - 1);
      ADJACENT_LIST[1 + N + work - 1].push_back(emply);
    }
  }

  for (int work = 1 + N; work < 1 + N + M; ++work)
  {
    COST[work][sink] = 0;
    COST[sink][work] = 0;
    CAPA[work][sink] = 1;
    FLOW[work][sink] = 0;
    FLOW[sink][work] = 0;
    ADJACENT_LIST[work].push_back(sink);
    ADJACENT_LIST[sink].push_back(work);
  }

  auto answer = Solve();

  cout << answer.first << "\n";
  cout << -answer.second << "\n";

  return 0;
}
