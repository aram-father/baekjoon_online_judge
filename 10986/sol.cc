#include <iostream>
#include <cstdint>

using namespace std;

const int64_t kMaxN = 1e6;
const int64_t kMaxM = 1e3;

int64_t N;
int64_t M;
int64_t NUMBER[kMaxN + 1];
int64_t PSUM[kMaxN + 1];
int64_t MOD[kMaxM];

int64_t Solve(void)
{
  int64_t answer = 0;

  // Build PSUM
  int64_t sum = 0;
  for (int64_t i = 1; i <= N; ++i)
  {
    sum += NUMBER[i];
    PSUM[i] = sum;
  }

  // Sweep
  MOD[0] = 1;
  for (int64_t i = 1; i <= N; ++i)
  {
    answer += MOD[PSUM[i] % M];
    ++MOD[PSUM[i] % M];
  }

  return answer;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N >> M;
  for (int i = 1; i <= N; ++i)
  {
    cin >> NUMBER[i];
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
