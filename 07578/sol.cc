#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

class SegmentTree
{
private:
  size_t number_of_elements_;
  vector<size_t> node_;

public:
  SegmentTree(const size_t number_of_elements) : number_of_elements_(number_of_elements)
  {
    size_t size = 1;
    while (size < number_of_elements_)
    {
      size *= 2;
    }
    node_.assign(2 * size, 0);
  }

private:
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

    size_t root_mid = (root_left + root_right) / 2;
    return Query(2 * root, root_left, root_mid, query_left, query_right) +
           Query(2 * root + 1, root_mid + 1, root_right, query_left, query_right);
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
      node_[root] = update_value;
      return node_[root];
    }

    size_t root_mid = (root_left + root_right) / 2;
    node_[root] = Update(2 * root, root_left, root_mid, update_index, update_value) +
                  Update(2 * root + 1, root_mid + 1, root_right, update_index, update_value);

    return node_[root];
  }

public:
  size_t Query(const size_t left, const size_t right)
  {
    return Query(1, 1, number_of_elements_, left, right);
  }

  void Update(const size_t index, const size_t value)
  {
    Update(1, 1, number_of_elements_, index, value);
  }

  const size_t number_of_elements(void) const
  {
    return number_of_elements_;
  }
};

SegmentTree* segment_tree = nullptr;

vector<size_t> machines;
map<size_t, size_t> machine_positions;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  size_t N;
  cin >> N;

  machines.assign(N, 0);
  for (auto& machine : machines)
  {
    cin >> machine;
  }

  for (size_t pos = 1; pos <= N; ++pos)
  {
    size_t machine;
    cin >> machine;
    machine_positions[machine] = pos;
  }

  // Solve
  segment_tree = new SegmentTree(N);

  size_t ret = 0;
  for (const auto& machine : machines)
  {
    ret += segment_tree->Query(machine_positions[machine], segment_tree->number_of_elements());
    segment_tree->Update(machine_positions[machine], 1);
  }

  cout << ret << "\n";

  return 0;
}
