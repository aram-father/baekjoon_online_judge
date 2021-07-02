#include <iostream>
#include <cstring>
#include <limits>
#include <algorithm>

using namespace std;

static const size_t kMaxN = 500000;
static const size_t kIdentity = 0;

struct XORTree
{
  size_t lazy[kMaxN * 4];
  size_t node[kMaxN * 4];
  size_t numb[kMaxN + 1];

  size_t Initialize(const size_t root, const size_t left, const size_t right)
  {
    if (left == right)
    {
      lazy[root] = kIdentity;
      node[root] = numb[left];
      return node[root];
    }

    size_t mid = (left + right) / 2;
    size_t left_tree = Initialize(2 * root, left, mid);
    size_t right_tree = Initialize(2 * root + 1, mid + 1, right);

    lazy[root] = kIdentity;
    node[root] = left_tree ^ right_tree;

    return node[root];
  }

  size_t Update(const size_t root, const size_t left, const size_t right, const size_t update_left,
                const size_t update_right, const size_t update)
  {
    if (update_right < left || right < update_left)
    {
      if ((right - left + 1) % 2)
      {
        return node[root] ^ lazy[root];
      }
      else
      {
        return node[root];
      }
    }

    if (update_left <= left && right <= update_right)
    {
      lazy[root] ^= update;

      if ((right - left + 1) % 2)
      {
        return node[root] ^ lazy[root];
      }
      else
      {
        return node[root];
      }
    }

    size_t mid = (left + right) / 2;
    size_t left_tree = Update(2 * root, left, mid, update_left, update_right, update);
    size_t right_tree = Update(2 * root + 1, mid + 1, right, update_left, update_right, update);

    node[root] = left_tree ^ right_tree;

    if ((right - left + 1) % 2)
    {
      return node[root] ^ lazy[root];
    }
    else
    {
      return node[root];
    }
  }

  size_t Query(const size_t root, const size_t left, const size_t right, const size_t query_left,
               const size_t query_right)
  {
    if (lazy[root] != kIdentity)
    {
      if (left != right)
      {
        lazy[2 * root] ^= lazy[root];
        lazy[2 * root + 1] ^= lazy[root];
      }

      if ((right - left + 1) % 2)
      {
        node[root] ^= lazy[root];
      }
      else
      {
        node[root] ^= kIdentity;
      }

      lazy[root] = kIdentity;
    }

    if (query_right < left || right < query_left)
    {
      return kIdentity;
    }

    if (query_left <= left && right <= query_right)
    {
      return node[root];
    }

    size_t mid = (left + right) / 2;
    size_t left_tree = Query(2 * root, left, mid, query_left, query_right);
    size_t right_tree = Query(2 * root + 1, mid + 1, right, query_left, query_right);

    return left_tree ^ right_tree;
  }

  void Traversal(size_t last)
  {
    for (size_t it = 1; it <= last; ++it)
    {
      cout << "tree[" << it << "] : " << node[it] << " / " << lazy[it] << "\n";
    }
  }
};

XORTree xor_tree;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  size_t N;
  cin >> N;

  for (size_t it = 1; it <= N; ++it)
  {
    cin >> xor_tree.numb[it];
  }

  xor_tree.Initialize(1, 1, N);
  // xor_tree.Traversal(9);

  size_t M;
  cin >> M;

  for (size_t it = 0; it < M; ++it)
  {
    size_t query;
    size_t left, right;
    size_t update;

    cin >> query;

    if (query == 1)
    {
      cin >> left >> right >> update;
      xor_tree.Update(1, 1, N, left + 1, right + 1, update);
      // xor_tree.Traversal(9);
    }
    else
    {
      cin >> left >> right;
      cout << xor_tree.Query(1, 1, N, left + 1, right + 1) << "\n";
      // xor_tree.Traversal(9);
    }
  }

  return 0;
}
