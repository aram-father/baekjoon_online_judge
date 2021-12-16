#include <iostream>
#include <utility>

using namespace std;

int main(void)
{
  pair<int, int> p1, p2, p3;

  cin >> p1.first >> p1.second;
  cin >> p2.first >> p2.second;
  cin >> p3.first >> p3.second;

  pair<int, int> v1(p2.first - p1.first, p2.second - p1.second);
  pair<int, int> v2(p3.first - p2.first, p3.second - p2.second);

  int cross = v1.first * v2.second - v1.second * v2.first;

  if (cross == 0)
  {
    cout << "0\n";
  }
  else if (cross < 0)
  {
    cout << "-1\n";
  }
  else
  {
    cout << "1\n";
  }

  return 0;
}
