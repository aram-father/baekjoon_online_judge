#include <iostream>
#include <vector>
#include <limits>
#include <cstdint>

using namespace std;

static const size_t kMaxN = 100000;

class SegmentTree
{
public:
  size_t n;
  size_t bars[kMaxN + 1];
  size_t node[4 * kMaxN];

public:
  SegmentTree(void) : n(0)
  {
    bars[0] = numeric_limits<size_t>::max();
  }

  size_t Initialize(const size_t root, const size_t left, const size_t right)
  {
    if (left == right)
    {
      node[root] = left;
      return node[root];
    }

    size_t mid = (left + right) / 2;
    size_t left_index = Initialize(2 * root, left, mid);
    size_t right_index = Initialize(2 * root + 1, mid + 1, right);

    node[root] = (bars[left_index] < bars[right_index]) ? left_index : right_index;

    return node[root];
  }

  size_t Query(const size_t root, const size_t left, const size_t right, const size_t query_left,
               const size_t query_right)
  {
    if (query_right < left || right < query_left)
    {
      return 0;
    }

    if (query_left <= left && right <= query_right)
    {
      return node[root];
    }

    size_t mid = (left + right) / 2;
    size_t left_index = Query(2 * root, left, mid, query_left, query_right);
    size_t right_index = Query(2 * root + 1, mid + 1, right, query_left, query_right);

    return (bars[left_index] < bars[right_index]) ? left_index : right_index;
  }
};

SegmentTree segment_tree;

int64_t Solve(SegmentTree& segment_tree, const size_t lo, const size_t hi)
{
  if (lo > hi)
  {
    return static_cast<int64_t>(0);
  }

  if (lo == hi)
  {
    return static_cast<int64_t>(segment_tree.bars[lo]);
  }

  size_t mid = segment_tree.Query(1, 1, segment_tree.n, lo, hi);

  int64_t ret = (hi - lo + 1) * segment_tree.bars[mid];

  ret = max(ret, Solve(segment_tree, lo, mid - 1));
  ret = max(ret, Solve(segment_tree, mid + 1, hi));

  return ret;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  while (true)
  {
    cin >> segment_tree.n;
    if (segment_tree.n == 0)
    {
      break;
    }

    for (size_t idx = 1; idx <= segment_tree.n; ++idx)
    {
      cin >> segment_tree.bars[idx];
    }

    segment_tree.Initialize(1, 1, segment_tree.n);

    cout << Solve(segment_tree, 1, segment_tree.n) << "\n";
  }

  return 0;
}
