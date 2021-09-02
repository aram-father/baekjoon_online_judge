#include <iostream>
#include <utility>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

size_t Solve(vector<pair<size_t, size_t> >& arr)
{
  stable_sort(arr.begin(), arr.end());

  size_t max_move = 0;

  for (size_t idx = 0; idx < arr.size(); ++idx)
  {
    if (arr[idx].second > idx)
    {
      max_move = max(max_move, arr[idx].second - idx);
    }
  }

  return max_move + 1;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  size_t N;

  cin >> N;
  vector<pair<size_t, size_t> > ARR(N);

  for (size_t it = 0; it < N; ++it)
  {
    cin >> ARR[it].first;
    ARR[it].second = it;
  }

  // Solve
  cout << Solve(ARR) << '\n';

  return 0;
}
