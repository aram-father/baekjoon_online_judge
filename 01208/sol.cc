#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> NUMS;

int64_t Solve(const vector<int>& nums, const int target)
{
  size_t lower = nums.size() / 2;
  size_t upper = nums.size() - lower;

  vector<int> lower_map((size_t)1 << lower);
  vector<int> upper_map((size_t)1 << upper);

  // Lower
  for (size_t mask = 0; mask < ((size_t)1 << lower); ++mask)
  {
    int sum = 0;
    for (size_t idx = 0; idx < lower; ++idx)
    {
      if (((size_t)1 << idx) & mask)
      {
        sum += nums[idx];
      }
    }

    lower_map[mask] = sum;
  }

  // Upper
  for (size_t mask = 0; mask < ((size_t)1 << upper); ++mask)
  {
    int sum = 0;
    for (size_t idx = 0; idx < upper; ++idx)
    {
      if (((size_t)1 << idx) & mask)
      {
        sum += nums[lower + idx];
      }
    }

    upper_map[mask] = sum;
  }

  sort(lower_map.begin(), lower_map.end());
  sort(upper_map.begin(), upper_map.end());

  // Two pointers
  int64_t ans = 0;
  auto left = lower_map.begin();
  auto right = upper_map.rbegin();

  while (left != lower_map.end() && right != upper_map.rend())
  {
    int sum = *left + *right;
    if (sum == target)
    {
      int64_t left_cnt = 1;
      int64_t right_cnt = 1;

      int left_prev = *left;
      int right_prev = *right;

      ++left;
      ++right;

      while (left != lower_map.end() && *left == left_prev)
      {
        ++left_cnt;
        ++left;
      }

      while (right != upper_map.rend() && *right == right_prev)
      {
        ++right_cnt;
        ++right;
      }

      ans += left_cnt * right_cnt;
    }
    else if (sum < target)
    {
      ++left;
    }
    else
    {
      ++right;
    }
  }

  return ans;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  int N, S;
  cin >> N >> S;

  NUMS.assign(N, 0);
  for (int it = 0; it < N; ++it)
  {
    cin >> NUMS[it];
  }

  // Solve
  cout << Solve(NUMS, S) - (S == 0 ? 1 : 0) << '\n';

  return 0;
}
