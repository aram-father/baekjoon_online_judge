#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int kMaxNumber = 10000;
const int kMinNumber = -10000;

size_t N;

priority_queue<int, vector<int>, less<int> > LEFT;
priority_queue<int, vector<int>, greater<int> > RIGHT;

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Add sentinels
  LEFT.emplace(kMinNumber - 1);
  LEFT.emplace(kMinNumber - 1);
  RIGHT.emplace(kMaxNumber + 1);
  RIGHT.emplace(kMaxNumber + 1);

  // Read Input
  cin >> N;
  for (size_t it = 0; it < N; ++it)
  {
    int number;
    cin >> number;

    if (LEFT.size() == RIGHT.size())
    {
      if (number <= LEFT.top())
      {
        LEFT.emplace(number);
      }
      else
      {
        RIGHT.emplace(number);
        LEFT.emplace(RIGHT.top());
        RIGHT.pop();
      }
    }
    else if (number <= LEFT.top())
    {
      LEFT.emplace(number);
      RIGHT.emplace(LEFT.top());
      LEFT.pop();
    }
    else
    {
      RIGHT.emplace(number);
    }

    cout << LEFT.top() << '\n';
  }

  return 0;
}
