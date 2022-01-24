#include <iostream>
#include <stack>
#include <utility>

using namespace std;

const int kMaxN = 1000000;

int N;
int A[kMaxN];
int F[kMaxN + 1];

void Solve()
{
  stack<int> answer;
  stack<pair<int, int> > st;

  for (int idx = N - 1; idx >= 0; --idx)
  {
    while (!st.empty() && st.top().first <= F[A[idx]])
    {
      st.pop();
    }

    answer.emplace(st.empty() ? -1 : st.top().second);
    st.emplace(F[A[idx]], A[idx]);
  }

  while (!answer.empty())
  {
    cout << answer.top() << ' ';
    answer.pop();
  }
  cout << '\n';
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;
  for (int it = 0; it < N; ++it)
  {
    cin >> A[it];
    ++F[A[it]];
  }

  // Solve
  Solve();

  return 0;
}
