#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

inline int abs(const int x)
{
  return x >= 0 ? x : -x;
}

struct Planet
{
  int id;
  int x, y, z;

  Planet(const int id, const int x, const int y, const int z) : id(id), x(x), y(y), z(z)
  {
  }
};

struct XComparator
{
  bool operator()(const Planet& a, const Planet& b)
  {
    return a.x < b.x;
  }
};

struct YComparator
{
  bool operator()(const Planet& a, const Planet& b)
  {
    return a.y < b.y;
  }
};

struct ZComparator
{
  bool operator()(const Planet& a, const Planet& b)
  {
    return a.z < b.z;
  }
};

struct Edge
{
  int src;
  int dst;
  int weight;
  Edge(const int src, const int dst, const int weight) : src(src), dst(dst), weight(weight)
  {
  }

  bool operator<(const Edge& rhs) const
  {
    return weight < rhs.weight;
  }
};

class DisjointSet
{
private:
  vector<int> parents_;

public:
  DisjointSet(const int size) : parents_(size, -1)
  {
  }

  int Find(const int elem)
  {
    if (parents_[elem] == -1)
    {
      return elem;
    }
    else
    {
      return (parents_[elem] = Find(parents_[elem]));
    }
  }

  void Union(const int a, const int b)
  {
    parents_[Find(a)] = Find(b);
  }
};

int N;
vector<Planet> PLANETS;
vector<Edge> EDGES;

int64_t Kruskal()
{
  int64_t answer = 0;

  DisjointSet dset((int)EDGES.size());
  sort(EDGES.begin(), EDGES.end());

  int num_of_planets = 1;

  for (const auto& edge : EDGES)
  {
    if (num_of_planets == N)
    {
      break;
    }

    if (dset.Find(edge.src) != dset.Find(edge.dst))
    {
      answer += edge.weight;
      dset.Union(edge.src, edge.dst);
      ++num_of_planets;
    }
  }

  return answer;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> N;
  for (int id = 0; id < N; ++id)
  {
    int x, y, z;
    cin >> x >> y >> z;
    PLANETS.emplace_back(id, x, y, z);
  }

  // Extract meaningful edges
  sort(PLANETS.begin(), PLANETS.end(), XComparator());
  for (size_t it = 0; it + 1 < PLANETS.size(); ++it)
  {
    EDGES.emplace_back(PLANETS[it].id, PLANETS[it + 1].id, abs(PLANETS[it].x - PLANETS[it + 1].x));
  }

  sort(PLANETS.begin(), PLANETS.end(), YComparator());
  for (size_t it = 0; it + 1 < PLANETS.size(); ++it)
  {
    EDGES.emplace_back(PLANETS[it].id, PLANETS[it + 1].id, abs(PLANETS[it].y - PLANETS[it + 1].y));
  }

  sort(PLANETS.begin(), PLANETS.end(), ZComparator());
  for (size_t it = 0; it + 1 < PLANETS.size(); ++it)
  {
    EDGES.emplace_back(PLANETS[it].id, PLANETS[it + 1].id, abs(PLANETS[it].z - PLANETS[it + 1].z));
  }

  // Kruskal
  cout << Kruskal() << '\n';
}
