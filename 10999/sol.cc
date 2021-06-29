#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

template <typename ElementType>
class SegTree
{
private:
  size_t number_of_elements_;
  vector<ElementType> lazy_;
  vector<ElementType> node_;

public:
  SegTree(const size_t number_of_elements) : number_of_elements_(number_of_elements)
  {
    size_t size = 1;
    while (size < number_of_elements_)
    {
      size *= 2;
    }

    lazy_.assign(size * 2, 0);
    node_.assign(size * 2, 0);
  }

private:
  void Propagate(const size_t root_index, const size_t root_range_left, const size_t root_range_right,
                 const ElementType propagation = 0)
  {
    if (root_range_left == root_range_right)
    {
      node_[root_index] += lazy_[root_index] + propagation;
      lazy_[root_index] = 0;
      return;
    }

    lazy_[root_index] += propagation;
    if (lazy_[root_index] == 0)
    {
      return;
    }

    const size_t root_left_index = 2 * root_index;
    const size_t root_right_index = 2 * root_index + 1;

    lazy_[root_left_index] += lazy_[root_index];
    lazy_[root_right_index] += lazy_[root_index];

    node_[root_index] += lazy_[root_index] * (root_range_right - root_range_left + 1);
    lazy_[root_index] = 0;

    return;
  }

  ElementType Query(const size_t root_index, const size_t root_range_left, const size_t root_range_right,
                    const size_t query_range_left, const size_t query_range_right)
  {
    if (root_range_right < query_range_left || query_range_right < root_range_left)
    {
      return static_cast<ElementType>(0);
    }

    Propagate(root_index, root_range_left, root_range_right);

    if (query_range_left <= root_range_left && root_range_right <= query_range_right)
    {
      return node_[root_index];
    }

    const size_t root_left_index = 2 * root_index;
    const size_t root_right_index = 2 * root_index + 1;
    const size_t root_range_mid = (root_range_left + root_range_right) / 2;

    ElementType left_sum = Query(root_left_index, root_range_left, root_range_mid, query_range_left, query_range_right);
    ElementType right_sum =
        Query(root_right_index, root_range_mid + 1, root_range_right, query_range_left, query_range_right);

    return left_sum + right_sum;
  }

  ElementType Update(const size_t root_index, const size_t root_range_left, const size_t root_range_right,
                     const size_t update_range_left, const size_t update_range_right, const ElementType update_value)
  {
    if (root_range_right < update_range_left || update_range_right < root_range_left)
    {
      return static_cast<ElementType>(node_[root_index] + lazy_[root_index] * (root_range_right - root_range_left + 1));
    }

    if (update_range_left <= root_range_left && root_range_right <= update_range_right)
    {
      lazy_[root_index] += update_value;
      return node_[root_index] + lazy_[root_index] * (root_range_right - root_range_left + 1);
    }

    const size_t root_left_index = 2 * root_index;
    const size_t root_right_index = 2 * root_index + 1;
    const size_t root_range_mid = (root_range_left + root_range_right) / 2;

    ElementType left_sum =
        Update(root_left_index, root_range_left, root_range_mid, update_range_left, update_range_right, update_value);
    ElementType right_sum = Update(root_right_index, root_range_mid + 1, root_range_right, update_range_left,
                                   update_range_right, update_value);

    node_[root_index] = left_sum + right_sum;

    return node_[root_index] + lazy_[root_index] * (root_range_right - root_range_left + 1);
  }

public:
  ElementType Query(const size_t left, const size_t right)
  {
    return Query(1, 1, number_of_elements_, left, right);
  }

  void Update(const size_t left, const size_t right, const ElementType add)
  {
    Update(1, 1, number_of_elements_, left, right, add);
  }
};

SegTree<int64_t>* seg_tree = nullptr;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input & Solve
  size_t N, M, K;
  cin >> N >> M >> K;

  seg_tree = new SegTree<int64_t>(N);

  for (size_t pos = 1; pos <= N; ++pos)
  {
    int64_t number;
    cin >> number;
    seg_tree->Update(pos, pos, number);
  }

  for (size_t it = 0; it < M + K; ++it)
  {
    size_t a, b, c;
    int64_t d;

    cin >> a;

    if (a == 1)
    {
      cin >> b >> c >> d;
      seg_tree->Update(b, c, d);
    }
    else
    {
      cin >> b >> c;
      cout << seg_tree->Query(b, c) << "\n";
    }
  }

  return 0;
}
