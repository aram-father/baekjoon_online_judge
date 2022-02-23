#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>

using namespace std;

size_t N;
int64_t S;
vector<int64_t> PSUM;

size_t Solve()
{
  size_t answer = N * 2;

  size_t lo = 1;
  size_t hi = 1;

  while (lo <= hi && hi <= N)
  {
    int64_t sum = PSUM[hi] - PSUM[lo - 1];
    if (sum >= S)
    {
      answer = min(answer, hi - lo + 1);
      ++lo;
    }
    else
    {
      ++hi;
    }
  }

  return answer > N ? 0 : answer;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> N >> S;
  PSUM.emplace_back(0);

  for (size_t it = 1; it <= N; ++it)
  {
    int64_t number;
    cin >> number;
    PSUM.emplace_back(number + PSUM[it - 1]);
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
