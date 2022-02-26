#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int T;
int N;
int M;
vector<int> PSUM_A;
vector<int> PSUM_B;
map<int, int> CAND_A;
map<int, int> CAND_B;

int main(void)
{
  scanf(" %d", &T);

  scanf(" %d", &N);
  PSUM_A.emplace_back(0);
  for (int it = 1; it <= N; ++it)
  {
    int a;
    scanf(" %d", &a);
    PSUM_A.emplace_back(a + PSUM_A[it - 1]);
  }

  scanf(" %d", &M);
  PSUM_B.emplace_back(0);
  for (int it = 1; it <= M; ++it)
  {
    int b;
    scanf(" %d", &b);
    PSUM_B.emplace_back(b + PSUM_B[it - 1]);
  }

  for (int i = 1; i <= N; ++i)
  {
    for (int j = i; j <= N; ++j)
    {
      ++CAND_A[PSUM_A[j] - PSUM_A[i - 1]];
    }
  }

  for (int i = 1; i <= M; ++i)
  {
    for (int j = i; j <= M; ++j)
    {
      ++CAND_B[PSUM_B[j] - PSUM_B[i - 1]];
    }
  }

  int64_t answer = 0;
  auto lo = CAND_A.begin();
  auto hi = CAND_B.rbegin();

  while (lo != CAND_A.end() && hi != CAND_B.rend())
  {
    int sum = lo->first + hi->first;
    if (sum == T)
    {
      answer += (int64_t)lo->second * (int64_t)hi->second;
      ++lo;
      ++hi;
    }
    else if (sum < T)
    {
      ++lo;
    }
    else
    {
      ++hi;
    }
  }

  printf("%ld\n", answer);

  return 0;
}
