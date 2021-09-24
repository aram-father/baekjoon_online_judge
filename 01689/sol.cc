#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

size_t N;
vector<pair<int, bool> > POINTS;

size_t Solve(void)
{
  sort(POINTS.begin(), POINTS.end());

  size_t ans = 0;
  size_t opened = 0;
  for (const auto& p : POINTS)
  {
    if (p.second)
    {
      ++opened;
      ans = max(ans, opened);
    }
    else
    {
      --opened;
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

  // Read Inputs
  cin >> N;
  for (size_t it = 0; it < N; ++it)
  {
    int s, e;
    cin >> s >> e;
    POINTS.emplace_back(s, true);
    POINTS.emplace_back(e, false);
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
