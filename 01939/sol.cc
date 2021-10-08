#include <iostream>
#include <vector>
#include <queue>

struct Edge
{
  size_t source_;
  size_t destination_;
  size_t capacity_;
  bool is_valid_;
};

using namespace std;

size_t N;
size_t M;
vector<Edge> EDGES;
vector<vector<Edge*> > MAP;
size_t S;
size_t D;

bool Bfs(void)
{
  vector<bool> visited(N, false);
  queue<size_t> q;

  visited[S - 1] = true;
  q.push(S - 1);

  while (!q.empty())
  {
    size_t here = q.front();
    q.pop();

    if (here == D - 1)
    {
      return true;
    }

    for (auto p_edge : MAP[here])
    {
      if (!p_edge->is_valid_)
      {
        continue;
      }

      size_t there = p_edge->destination_;
      if (!visited[there])
      {
        visited[there] = true;
        q.push(there);
      }
    }
  }

  return false;
}

size_t Solve(void)
{
  size_t left = 1;
  size_t right = 1000000000 + 1;

  while (left < right)
  {
    size_t middle = (left + right) / 2;

    for (auto& edge : EDGES)
    {
      if (edge.capacity_ < middle)
      {
        edge.is_valid_ = false;
      }
    }

    if (Bfs())
    {
      left = middle + 1;
    }
    else
    {
      right = middle;
    }

    for (auto& edge : EDGES)
    {
      edge.is_valid_ = true;
    }
  }

  return left - 1;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  cin >> N >> M;
  EDGES.assign(2 * M, Edge());
  MAP.assign(N, vector<Edge*>());

  for (size_t it = 0; it < M; ++it)
  {
    size_t src, dst, capa;
    cin >> src >> dst >> capa;

    EDGES[it].source_ = src - 1;
    EDGES[it].destination_ = dst - 1;
    EDGES[it].capacity_ = capa;
    EDGES[it].is_valid_ = true;

    EDGES[it + M].source_ = dst - 1;
    EDGES[it + M].destination_ = src - 1;
    EDGES[it + M].capacity_ = capa;
    EDGES[it + M].is_valid_ = true;

    MAP[src - 1].push_back(&EDGES[it]);
    MAP[dst - 1].push_back(&EDGES[it + M]);
  }

  cin >> S >> D;

  // Solve
  cout << Solve() << '\n';

  return 0;
}
