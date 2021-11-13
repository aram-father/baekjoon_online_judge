#include <iostream>
#include <cstdint>
#include <utility>
#include <stack>

using namespace std;

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs & Solve
  int n;
  cin >> n;

  int64_t answer = 0;

  int height;
  stack<pair<int, int> > st;

  cin >> height;
  st.push(pair<int, int>(height, 1));

  for (int it = 1; it < n; ++it)
  {
    cin >> height;

    if (st.top().first > height)
    {
      answer += 1;
      st.push(pair<int, int>(height, 1));
      continue;
    }

    while (!st.empty() && st.top().first < height)
    {
      answer += st.top().second;
      st.pop();
    }

    if (st.empty())
    {
      st.push(pair<int, int>(height, 1));
    }
    else if (st.top().first == height)
    {
      auto prev = st.top();
      st.pop();

      if (st.empty())
      {
        answer += prev.second;
      }
      else
      {
        answer += prev.second + 1;
      }

      prev.second += 1;
      st.push(prev);
    }
    else
    {
      answer += 1;
      st.push(pair<int, int>(height, 1));
    }
  }

  cout << answer << '\n';

  return 0;
}
