#include <iostream>
#include <cstdint>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

const size_t kMaxN = 10000;
const size_t kMaxM = 50000;
const size_t kMaxK = 20;
const size_t kMaxW = 1000000;

size_t N, M, K;
vector<pair<size_t, size_t> > AL[kMaxN];

bool VISIT[kMaxN];
int64_t DIST[kMaxK + 1][kMaxN];

void Dijkstra(const size_t src)
{
  priority_queue<tuple<int64_t, size_t, size_t> > pq;

  DIST[0][src] = 0;
  pq.emplace(-DIST[0][src], src, 0);

  while (!pq.empty())
  {
    int64_t dist = -get<0>(pq.top());
    size_t here = get<1>(pq.top());
    size_t pave = get<2>(pq.top());
    pq.pop();

    if (DIST[pave][here] < dist)
    {
      continue;
    }

    for (const auto& neighbor : AL[here])
    {
      size_t there = neighbor.second;
      int64_t weight = static_cast<int64_t>(neighbor.first);

      // not pave
      if (dist + weight < DIST[pave][there])
      {
        DIST[pave][there] = dist + weight;
        pq.emplace(-DIST[pave][there], there, pave);
      }

      // pave
      if (pave < K && dist < DIST[pave + 1][there])
      {
        DIST[pave + 1][there] = dist;
        pq.emplace(-DIST[pave + 1][there], there, pave + 1);
      }
    }
  }
}

int main(void)
{
  // Initialize
  for (size_t i = 0; i < kMaxN; ++i)
  {
    VISIT[i] = false;
  }

  for (size_t i = 0; i < kMaxK + 1; ++i)
  {
    for (size_t j = 0; j < kMaxN; ++j)
    {
      DIST[i][j] = static_cast<int64_t>(kMaxW * kMaxN * 100);
    }
  }

  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> N >> M >> K;
  for (size_t it = 0; it < M; ++it)
  {
    size_t src, dst, weight;
    cin >> src >> dst >> weight;

    AL[src - 1].emplace_back(weight, dst - 1);
    AL[dst - 1].emplace_back(weight, src - 1);
  }

  // Solve
  Dijkstra(0);

  // Print answer
  int64_t ans = kMaxW * kMaxN * 100;
  for (size_t it = 0; it < kMaxK + 1; ++it)
  {
    ans = min(ans, DIST[it][N - 1]);
  }

  cout << ans << '\n';

  return 0;
}
