#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

static const int kMaxN = 100;
static const int kMaxM = 20000;
static const int kMaxW = 1000;

int WEIGHT[kMaxN][kMaxN];

bool Bfs(const vector<vector<pair<int, int> > >& adjacent_list, const int source, const set<int>& destinations)
{
  vector<bool> visited(adjacent_list.size(), false);
  queue<int> q;

  visited[source] = true;
  q.push(source);

  while (!q.empty())
  {
    int here = q.front();

    if (destinations.find(here) != destinations.end())
    {
      return true;
    }

    q.pop();

    for (const auto& neighbor : adjacent_list[here])
    {
      if (!visited[neighbor.second])
      {
        visited[neighbor.second] = true;
        q.push(neighbor.second);
      }
    }
  }

  return false;
}

bool Bfs2(const vector<vector<pair<int, int> > >& adjacent_list, const int destination, const set<int>& sources)
{
  vector<bool> visited(adjacent_list.size(), false);
  queue<int> q;

  for (const auto& source : sources)
  {
    if (visited[source])
    {
      continue;
    }

    visited[source] = true;
    q.push(source);

    while (!q.empty())
    {
      int here = q.front();

      if (here == destination)
      {
        return true;
      }

      q.pop();

      for (const auto& neighbor : adjacent_list[here])
      {
        if (!visited[neighbor.second])
        {
          visited[neighbor.second] = true;
          q.push(neighbor.second);
        }
      }
    }
  }

  return false;
}

void Solve(const vector<vector<pair<int, int> > >& adjacent_list, const int source, const int destination)
{
  vector<int> distances(adjacent_list.size(), kMaxN * kMaxW + 1);
  vector<int> prev(adjacent_list.size(), -1);
  set<int> vertices_in_cycle;

  distances[source] = 0;

  size_t loop_cnt = 0;
  while (loop_cnt < adjacent_list.size())
  {
    bool relaxed = false;

    for (int here = 0; here < (int)adjacent_list.size(); ++here)
    {
      for (const auto& neighbor : adjacent_list[here])
      {
        int there = neighbor.second;
        int weight = neighbor.first;

        if (distances[there] > distances[here] + weight)
        {
          relaxed = true;
          prev[there] = here;
          distances[there] = distances[here] + weight;

          if (loop_cnt + 1 == adjacent_list.size())
          {
            vertices_in_cycle.insert(here);
          }
        }
      }
    }

    if (!relaxed)
    {
      break;
    }

    ++loop_cnt;
  }

  if (vertices_in_cycle.size() != 0 && Bfs(adjacent_list, source, vertices_in_cycle) &&
      Bfs2(adjacent_list, destination, vertices_in_cycle))
  {
    cout << -1 << "\n";
    return;
  }

  vector<int> path;

  int current = destination;
  while (current != source)
  {
    path.push_back(current);
    current = prev[current];
  }
  path.push_back(source);

  for (auto it = path.rbegin(); it != path.rend(); ++it)
  {
    cout << (*it) + 1 << ' ';
  }
  cout << "\n";
}

int main(void)
{
  // Initialize
  for (int i = 0; i < kMaxN; ++i)
  {
    for (int j = 0; j < kMaxN; ++j)
    {
      WEIGHT[i][j] = kMaxW + 1;
    }
  }

  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  int N, M;
  cin >> N >> M;

  vector<vector<pair<int, int> > > adjacent_list(N, vector<pair<int, int> >());

  for (int it = 0; it < M; ++it)
  {
    int u, v, w;
    cin >> u >> v >> w;

    if (WEIGHT[u - 1][v - 1] == kMaxW + 1)
    {
      WEIGHT[u - 1][v - 1] = -w;
    }
    else
    {
      WEIGHT[u - 1][v - 1] = min(WEIGHT[u - 1][v - 1], -w);
    }

    adjacent_list[u - 1].emplace_back(WEIGHT[u - 1][v - 1], v - 1);
  }

  Solve(adjacent_list, 0, N - 1);

  return 0;
}
