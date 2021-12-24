#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

const int kS = 0;
const int kE = 1;
const int kT11 = 2;
const int kT12 = 3;
const int kT21 = 4;
const int kT22 = 5;
const int kT31 = 6;
const int kT32 = 7;
const int kN = 8;

int64_t Dijkstra(const vector<vector<pair<int, int>>>& adj, const int src, const int dst)
{
  vector<int64_t> min_dist(adj.size(), numeric_limits<int64_t>::max());
  priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<pair<int64_t, int>>> pq;

  min_dist[src] = 0;
  pq.emplace(min_dist[src], src);

  while (!pq.empty())
  {
    int here = pq.top().second;
    int64_t dist = pq.top().first;
    pq.pop();

    if (dist > min_dist[here])
    {
      continue;
    }

    for (const auto& neighbor : adj[here])
    {
      int there = neighbor.first;
      int cost = neighbor.second;

      if (dist + cost < min_dist[there])
      {
        min_dist[there] = dist + cost;
        pq.emplace(min_dist[there], there);
      }
    }
  }

  return min_dist[dst];
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  vector<pair<int, int>> vertices(kN);
  for (int i = 0; i < kN; ++i)
  {
    cin >> vertices[i].first;
    cin >> vertices[i].second;
  }

  // Build adjacency list
  vector<vector<pair<int, int>>> adj(kN, vector<pair<int, int>>());
  for (int src = 0; src < kN; ++src)
  {
    for (int dst = src + 1; dst < kN; ++dst)
    {
      int man_dist = abs(vertices[src].first - vertices[dst].first) + abs(vertices[src].second - vertices[dst].second);
      adj[src].emplace_back(dst, man_dist);
      adj[dst].emplace_back(src, man_dist);

      if ((src == kT11 && dst == kT12) || (src == kT12 && dst == kT11))
      {
        adj[src].emplace_back(dst, 10);
        adj[dst].emplace_back(src, 10);
      }

      if ((src == kT21 && dst == kT22) || (src == kT22 && dst == kT21))
      {
        adj[src].emplace_back(dst, 10);
        adj[dst].emplace_back(src, 10);
      }

      if ((src == kT31 && dst == kT32) || (src == kT32 && dst == kT31))
      {
        adj[src].emplace_back(dst, 10);
        adj[dst].emplace_back(src, 10);
      }
    }
  }

  // Solve
  cout << Dijkstra(adj, kS, kE) << '\n';

  return 0;
}
