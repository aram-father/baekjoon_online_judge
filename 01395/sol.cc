#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

static const size_t kMaxN = 100000;

class OddEvenTree
{
private:
  size_t lazy_[kMaxN * 4];
  pair<size_t, size_t> node_[kMaxN * 4];

public:
  OddEvenTree(void)
  {
    memset(lazy_, 0, sizeof(size_t) * kMaxN * 4);
  }

  pair<size_t, size_t> Initialize(const size_t root, const size_t left, const size_t right)
  {
    if (left == right)
    {
      node_[root] = pair<size_t, size_t>(0, 1);
      return node_[root];
    }

    size_t mid = (left + right) / 2;
    auto left_tree = Initialize(2 * root, left, mid);
    auto right_tree = Initialize(2 * root + 1, mid + 1, right);

    node_[root] = pair<size_t, size_t>(left_tree.first + right_tree.first, left_tree.second + right_tree.second);

    return node_[root];
  }

  pair<size_t, size_t> Toggle(const size_t root, const size_t left, const size_t right, const size_t toggle_left,
                              const size_t toggle_right)
  {
    if (right < toggle_left || toggle_right < left)
    {
      if (lazy_[root] % 2)
      {
        return pair<size_t, size_t>(node_[root].second, node_[root].first);
      }

      return node_[root];
    }

    if (toggle_left <= left && right <= toggle_right)
    {
      lazy_[root] += 1;

      if (lazy_[root] % 2)
      {
        return pair<size_t, size_t>(node_[root].second, node_[root].first);
      }

      return node_[root];
    }

    size_t mid = (left + right) / 2;
    auto left_tree = Toggle(2 * root, left, mid, toggle_left, toggle_right);
    auto right_tree = Toggle(2 * root + 1, mid + 1, right, toggle_left, toggle_right);

    node_[root] = pair<size_t, size_t>(left_tree.first + right_tree.first, left_tree.second + right_tree.second);

    if (lazy_[root] % 2)
    {
      return pair<size_t, size_t>(node_[root].second, node_[root].first);
    }

    return node_[root];
  }

  pair<size_t, size_t> Query(const size_t root, const size_t left, const size_t right, const size_t query_left,
                             const size_t query_right)
  {
    if (lazy_[root] != 0)
    {
      if (left != right)
      {
        lazy_[2 * root] += lazy_[root];
        lazy_[2 * root + 1] += lazy_[root];
      }

      if (lazy_[root] % 2)
      {
        swap(node_[root].first, node_[root].second);
      }

      lazy_[root] = 0;
    }

    if (right < query_left || query_right < left)
    {
      return pair<size_t, size_t>(0, 0);
    }

    if (query_left <= left && right <= query_right)
    {
      return node_[root];
    }

    size_t mid = (left + right) / 2;
    auto left_tree = Query(2 * root, left, mid, query_left, query_right);
    auto right_tree = Query(2 * root + 1, mid + 1, right, query_left, query_right);

    return pair<size_t, size_t>(left_tree.first + right_tree.first, left_tree.second + right_tree.second);
  }
};

OddEvenTree odd_even_tree;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  size_t N, M;
  cin >> N >> M;

  odd_even_tree.Initialize(1, 1, N);

  for (size_t it = 0; it < M; ++it)
  {
    size_t o, s, t;
    cin >> o >> s >> t;

    if (o)
    {
      cout << odd_even_tree.Query(1, 1, N, s, t).first << "\n";
    }
    else
    {
      odd_even_tree.Toggle(1, 1, N, s, t);
    }
  }

  return 0;
}
