#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class DisjointSet
{
private:
  vector<int> parent_;

public:
  DisjointSet()
  {
  }

  DisjointSet(const int size) : parent_(size, -1)
  {
  }

  void Assign(const int size)
  {
    parent_.assign(size, -1);
  }

  int Find(const int x)
  {
    if (parent_[x] == -1)
    {
      return x;
    }
    else
    {
      return (parent_[x] = Find(parent_[x]));
    }
  }

  void Union(const int x, const int y)
  {
    parent_[Find(y)] = Find(x);
  }
};

class Edge
{
public:
  int src_;
  int dst_;
  int cost_;

  Edge(const int src, const int dst, const int cost) : src_(src), dst_(dst), cost_(cost)
  {
  }

  bool operator<(const Edge& rhs) const
  {
    return cost_ < rhs.cost_;
  }
};

int N, M;
DisjointSet villages;
vector<Edge> edges;

int Solve()
{
  sort(edges.begin(), edges.end());
  villages.Assign(N + 1);

  int max_bridge = -1;
  int answer = 0;
  for (const auto& edge : edges)
  {
    if (villages.Find(edge.src_) != villages.Find(edge.dst_))
    {
      villages.Union(edge.src_, edge.dst_);
      answer += edge.cost_;

      if (edge.cost_ > max_bridge)
      {
        max_bridge = edge.cost_;
      }
    }
  }

  return answer - max_bridge;
}

int main(void)
{
  scanf(" %d %d", &N, &M);

  for (int it = 0; it < M; ++it)
  {
    int src, dst, cost;
    scanf(" %d %d %d", &src, &dst, &cost);
    edges.emplace_back(src, dst, cost);
  }

  printf("%d\n", Solve());

  return 0;
}
