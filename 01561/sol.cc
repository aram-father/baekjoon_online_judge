#include <iostream>
#include <vector>

using namespace std;

size_t N;
size_t M;
vector<size_t> RIDES;

size_t Solve(void)
{
  size_t left = 0;
  size_t right = N * 30;

  while (left < right)
  {
    size_t middle = (left + right) / 2;

    size_t served = 0;
    for (const auto& ride : RIDES)
    {
      served += middle / ride + 1;
    }

    if (served >= N)
    {
      right = middle;
    }
    else
    {
      left = middle + 1;
    }
  }

  size_t pre_served = 0;
  if (right != 0)
  {
    for (const auto& ride : RIDES)
    {
      pre_served += (right - 1) / ride + 1;
    }
  }

  size_t cur_served = 0;
  for (size_t idx = 0; idx < RIDES.size(); ++idx)
  {
    if (right % RIDES[idx] == 0)
    {
      if (++cur_served == N - pre_served)
      {
        return idx + 1;
      }
    }
  }

  return 0;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N >> M;
  for (size_t it = 1; it <= M; ++it)
  {
    size_t time;
    cin >> time;
    RIDES.emplace_back(time);
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
