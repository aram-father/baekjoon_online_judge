#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

int N;

class Vector
{
public:
  int64_t x, y;

  Vector()
  {
  }
  Vector(const int64_t x, const int64_t y) : x(x), y(y)
  {
  }

  int64_t operator*(const Vector& rhs) const
  {
    return x * rhs.y - y * rhs.x;
  }

  Vector operator-(const Vector& rhs) const
  {
    return Vector(x - rhs.x, y - rhs.y);
  }

  bool operator<(const Vector& rhs) const
  {
    if (x != rhs.x)
    {
      return x < rhs.x;
    }

    return y < rhs.y;
  }
};

class Line
{
public:
  Vector start, end;

  Line()
  {
  }
  Line(const Vector& start, const Vector& end) : start(start), end(end)
  {
    if (end < start)
    {
      swap<Vector>(this->start, this->end);
    }
  }
};

bool HasIntersect(const Line& l1, const Line& l2)
{
  int64_t l1_l2 = ((l1.end - l1.start) * (l2.start - l1.end)) * ((l1.end - l1.start) * (l2.end - l1.end));
  int64_t l2_l1 = ((l2.end - l2.start) * (l1.start - l2.end)) * ((l2.end - l2.start) * (l1.end - l2.end));

  if (l1_l2 == 0 && l2_l1 == 0)
  {
    return !(l1.end < l2.start || l2.end < l1.start);
  }

  return l1_l2 <= 0 && l2_l1 <= 0;
}

class Set
{
public:
  vector<int> parent;
  vector<int> number_of_elem;
  Set(const int size) : parent(size, -1), number_of_elem(size, 1)
  {
  }
  int Find(const int idx)
  {
    if (parent[idx] != -1)
    {
      parent[idx] = Find(parent[idx]);
      return parent[idx];
    }
    return idx;
  }
  void Union(const int a, const int b)
  {
    int root_a = Find(a);
    int root_b = Find(b);
    if (root_a == root_b)
    {
      return;
    }
    parent[root_a] = root_b;
    number_of_elem[root_b] += number_of_elem[root_a];
  }
};

void Solve(const vector<Line>& lines)
{
  Set dset(N);

  for (int i = 0; i < N; ++i)
  {
    for (int j = i + 1; j < N; ++j)
    {
      if (HasIntersect(lines[i], lines[j]))
      {
        dset.Union(i, j);
      }
    }
  }

  int number_of_group = 0;
  int max_group_size = -1;

  for (int i = 0; i < N; ++i)
  {
    if (dset.parent[i] == -1)
    {
      ++number_of_group;
      max_group_size = max(max_group_size, dset.number_of_elem[i]);
    }
  }

  printf("%d\n%d\n", number_of_group, max_group_size);
}

int main(void)
{
  // Read input
  scanf(" %d", &N);
  vector<Line> lines;
  for (int it = 0; it < N; ++it)
  {
    Vector start, end;
    scanf(" %ld %ld %ld %ld", &start.x, &start.y, &end.x, &end.y);
    lines.emplace_back(start, end);
  }

  // Solve
  Solve(lines);

  return 0;
}