#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <memory>
#include <queue>
#include <cstring>

using namespace std;

static const size_t kMaxPoints = 75000;

class CountTree
{
private:
  size_t size_;
  size_t node_[kMaxPoints * 4];

  size_t Query(const size_t root, const size_t root_left, const size_t root_right, const size_t query_left,
               const size_t query_right)
  {
    if (root_right < query_left || query_right < root_left)
    {
      return 0;
    }

    if (query_left <= root_left && root_right <= query_right)
    {
      return node_[root];
    }

    const size_t root_mid = (root_left + root_right) / 2;
    const size_t left_tree = Query(2 * root, root_left, root_mid, query_left, query_right);
    const size_t right_tree = Query(2 * root + 1, root_mid + 1, root_right, query_left, query_right);

    return left_tree + right_tree;
  }

  size_t Update(const size_t root, const size_t root_left, const size_t root_right, const size_t update_index,
                const size_t update_value)
  {
    if (root_right < update_index || update_index < root_left)
    {
      return node_[root];
    }

    if (root_left == root_right)
    {
      return (node_[root] += update_value);
    }

    const size_t root_mid = (root_left + root_right) / 2;
    const size_t left_tree = Update(2 * root, root_left, root_mid, update_index, update_value);
    const size_t right_tree = Update(2 * root + 1, root_mid + 1, root_right, update_index, update_value);

    return (node_[root] = left_tree + right_tree);
  }

public:
  void Initialize(const size_t size)
  {
    size_ = size;
    memset(node_, 0, sizeof(size_t) * size_ * 4);
  }

  size_t Query(const size_t left, const size_t right)
  {
    return Query(1, 1, size_, left, right);
  }

  void Update(const size_t update_index, const size_t update_value)
  {
    Update(1, 1, size_, update_index, update_value);
  }
};

bool compare(const pair<int, int>& left, const pair<int, int>& right)
{
  if (left.first != right.first)
  {
    return left.first < right.first;
  }

  return left.second > right.second;
}

CountTree p_tree;

size_t Solve(std::map<int, int>& y_map, vector<pair<int, int> >& points)
{
  // Build map
  size_t idx = 0;
  for (auto& y : y_map)
  {
    y.second = ++idx;
  }

  // Prepare segment tree
  p_tree.Initialize(y_map.size());

  // Solve
  size_t ret = 0;

  sort(points.begin(), points.end(), compare);

  for (const auto& point : points)
  {
    int y = point.second;

    ret += p_tree.Query(y_map[y], y_map.size());
    p_tree.Update(y_map[y], 1);
  }

  return ret;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  size_t testcase;
  cin >> testcase;

  while (testcase--)
  {
    size_t n;
    cin >> n;

    // Read input & compress coordinate
    std::map<int, int> y_map;
    vector<pair<int, int> > points;

    for (size_t it = 0; it < n; ++it)
    {
      int x, y;
      cin >> x >> y;

      y_map[y] = 0;

      points.emplace_back(x, y);
    }

    cout << Solve(y_map, points) << "\n";
  }

  return 0;
}
