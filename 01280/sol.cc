#include <iostream>

using namespace std;

static const int64_t kMaxX = 200000 + 1;
static const int64_t kMod = 1000000007;

class FenwickTree
{
private:
  int64_t node_[kMaxX + 1];

public:
  FenwickTree(void)
  {
    for (int64_t it = 0; it < kMaxX + 1; ++it)
    {
      node_[it] = 0;
    }
  }

  void Update(const int64_t idx, const int64_t value)
  {
    int64_t index = idx;

    while (true)
    {
      node_[index] += value;
      index += index & (-index);

      if (index > kMaxX)
      {
        break;
      }
    }
  }

  int64_t Psum(const int64_t idx)
  {
    int64_t index = idx;

    int64_t ret = 0;

    while (true)
    {
      ret += node_[index];
      index -= index & (-index);

      if (index <= 0)
      {
        break;
      }
    }

    return ret;
  }
};

FenwickTree val_tree;
FenwickTree cnt_tree;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Solve
  int64_t N;
  cin >> N;

  int64_t first;
  cin >> first;

  val_tree.Update(first + 1, first + 1);
  cnt_tree.Update(first + 1, 1);

  int64_t ret = 1;
  for (int64_t it = 1; it < N; ++it)
  {
    int64_t number;
    cin >> number;

    int64_t b_val = val_tree.Psum(kMaxX) - val_tree.Psum(number);
    int64_t s_val = val_tree.Psum(number);

    int64_t b_cnt = cnt_tree.Psum(kMaxX) - cnt_tree.Psum(number);
    int64_t s_cnt = cnt_tree.Psum(number);

    int64_t dist = s_cnt * (number + 1) - s_val + b_val - b_cnt * (number + 1);
    ret = (ret * (dist % kMod)) % kMod;

    val_tree.Update(number + 1, number + 1);
    cnt_tree.Update(number + 1, 1);
  }

  cout << ret << "\n";

  return 0;
}
