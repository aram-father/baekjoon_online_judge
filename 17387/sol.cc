#include <iostream>
#include <limits>
#include <utility>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point
{
  double x, y;
  Point(const double x = 0, const double y = 0) : x(x), y(y)
  {
  }
  Point operator-(const Point& rhs) const
  {
    return Point(x - rhs.x, y - rhs.y);
  }
  double Cross(const Point& rhs) const
  {
    return x * rhs.y - y * rhs.x;
  }
  bool operator<(const Point& rhs) const
  {
    return x == rhs.x ? y < rhs.y : x < rhs.x;
  }
};

struct Line
{
  Point s, e;
};

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  Line l1, l2;
  cin >> l1.s.x >> l1.s.y >> l1.e.x >> l1.e.y;
  cin >> l2.s.x >> l2.s.y >> l2.e.x >> l2.e.y;

  double l1_cross = (l1.e - l1.s).Cross(l2.e - l1.s) * (l1.e - l1.s).Cross(l2.s - l1.s);
  double l2_cross = (l2.e - l2.s).Cross(l1.e - l2.s) * (l2.e - l2.s).Cross(l1.s - l2.s);

  if (l1_cross == 0 && l2_cross == 0)
  {
    if (l1.e < l1.s)
    {
      swap(l1.s, l1.e);
    }
    if (l2.e < l2.s)
    {
      swap(l2.s, l2.e);
    }

    if (l1.e < l2.s || l2.e < l1.s)
    {
      cout << "0\n";
    }
    else
    {
      cout << "1\n";
    }
  }
  else if (l1_cross <= 0 && l2_cross <= 0)
  {
    cout << "1\n";
  }
  else
  {
    cout << "0\n";
  }

  return 0;
}
