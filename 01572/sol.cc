#include <iostream>
#include <cstring>
#include <cstdint>

using namespace std;

static const int kMaxN = 65536 + 1;

class KthTree
{
private:
  int count_[4 * kMaxN];

public:
  KthTree(void)
  {
    memset(count_, 0, sizeof(int) * 4 * kMaxN);
  }

  int Diff(const int root, const int left, const int right, const int diff_index, const int diff_value)
  {
    if (diff_index < left || right < diff_index)
    {
      return count_[root];
    }

    if (left == right)
    {
      count_[root] += diff_value;
      return count_[root];
    }

    int mid = (left + right) / 2;
    count_[root] =
        Diff(2 * root, left, mid, diff_index, diff_value) + Diff(2 * root + 1, mid + 1, right, diff_index, diff_value);

    return count_[root];
  }

  int GetKth(const int root, const int left, const int right, const int k)
  {
    if (left == right)
    {
      return left;
    }

    int left_count = count_[2 * root];
    int mid = (left + right) / 2;

    if (k <= left_count)
    {
      return GetKth(2 * root, left, mid, k);
    }
    else
    {
      return GetKth(2 * root + 1, mid + 1, right, k - left_count);
    }
  }
};

int numbers[250000];
KthTree kth_tree;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  int N, K;
  cin >> N >> K;

  for (int it = 0; it < N; ++it)
  {
    cin >> numbers[it];
  }

  // Solve
  int64_t sum = 0;

  for (int it = 0; it < K; ++it)
  {
    kth_tree.Diff(1, 1, kMaxN, numbers[it] + 1, 1);
  }

  sum += kth_tree.GetKth(1, 1, kMaxN, (1 + K) / 2) - 1;

  for (int it = K; it < N; ++it)
  {
    kth_tree.Diff(1, 1, kMaxN, numbers[it - K] + 1, -1);
    kth_tree.Diff(1, 1, kMaxN, numbers[it] + 1, 1);

    sum += kth_tree.GetKth(1, 1, kMaxN, (1 + K) / 2) - 1;
  }

  cout << sum << "\n";

  return 0;
}
