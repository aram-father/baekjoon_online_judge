#include <iostream>
#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  size_t N;
  cin >> N;

  vector<pair<int, int> > POINTS;

  for (size_t it = 0; it < N; ++it)
  {
    int X, Y;
    cin >> X >> Y;
    POINTS.emplace_back(X, 1);
    POINTS.emplace_back(Y, 0);
  }

  sort(POINTS.begin(), POINTS.end());

  int64_t sum = 0;

  int prev = POINTS[0].first;
  size_t opened_points = 0;
  for (const auto& point : POINTS)
  {
    if (opened_points > 0)
    {
      sum += point.first - prev;
    }

    if (point.second == 1)
    {
      ++opened_points;
    }
    else
    {
      --opened_points;
    }

    prev = point.first;
  }

  cout << sum << "\n";

  return 0;
}
