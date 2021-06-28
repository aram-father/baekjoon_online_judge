#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

int Prim(const vector<vector<pair<int, int> > >& adjacent_list, const int source)
{
  int ret = 0;

  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
  vector<int> distances(adjacent_list.size(), numeric_limits<int>::max());
  vector<bool> visited(adjacent_list.size(), false);

  distances[source] = 0;
  pq.emplace(distances[source], source);

  while (!pq.empty())
  {
    int here = pq.top().second;
    int cost = pq.top().first;
    pq.pop();

    if (distances[here] < cost)
    {
      continue;
    }

    visited[here] = true;
    ret += cost;

    for (const auto& neighbor : adjacent_list[here])
    {
      int there = neighbor.second;
      int weight = neighbor.first;

      if (!visited[there] && distances[there] > weight)
      {
        distances[there] = weight;
        pq.emplace(weight, there);
      }
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
  int V, E;
  cin >> V >> E;

  vector<vector<pair<int, int> > > adjacent_list(V, vector<pair<int, int> >());

  for (int it = 0; it < E; ++it)
  {
    int A, B, C;
    cin >> A >> B >> C;

    adjacent_list[A - 1].emplace_back(C, B - 1);
    adjacent_list[B - 1].emplace_back(C, A - 1);
  }

  cout << Prim(adjacent_list, 0) << "\n";

  return 0;
}
