#include <cstdio>
#include <cmath>
#include <algorithm>
#include <limits>
#include <vector>
#include <cstdint>

using namespace std;

const int kMaxN = 20;

int N;
int XS[kMaxN];
int YS[kMaxN];

double Solve()
{
  vector<int> tickets(N, 0);
  for (int it = N / 2; it < N; ++it)
  {
    tickets[it] = 1;
  }

  double answer_sq = numeric_limits<double>::max();

  do
  {
    int64_t pos_x = 0;
    int64_t pos_y = 0;

    int64_t neg_x = 0;
    int64_t neg_y = 0;

    for (int it = 0; it < N; ++it)
    {
      if (tickets[it] == 0)
      {
        pos_x += XS[it];
        pos_y += YS[it];
      }
      else
      {
        neg_x += XS[it];
        neg_y += YS[it];
      }
    }

    double los_sq = (pos_x - neg_x) * (pos_x - neg_x) + (pos_y - neg_y) * (pos_y - neg_y);
    if (answer_sq > los_sq)
    {
      answer_sq = los_sq;
    }

  } while (next_permutation(tickets.begin(), tickets.end()));

  return answer_sq;
}

int main(void)
{
  int testcase;
  scanf(" %d", &testcase);

  while (testcase--)
  {
    scanf(" %d", &N);
    for (int it = 0; it < N; ++it)
    {
      scanf(" %d %d", &XS[it], &YS[it]);
    }

    printf("%lf\n", sqrt(Solve()));
  }

  return 0;
}
