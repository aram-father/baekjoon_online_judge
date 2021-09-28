#include <iostream>
#include <queue>
#include <vector>
#include <set>

using namespace std;

size_t N;
size_t M;
set<size_t> FORWARD_ADJ[32000];
set<size_t> REVERSE_ADJ[32000];

void Solve(void)
{
  priority_queue<size_t, vector<size_t>, greater<size_t> > pq;

  for (size_t dst = 0; dst < N; ++dst)
  {
    if (REVERSE_ADJ[dst].size() == 0)
    {
      pq.emplace(dst);
    }
  }

  while (!pq.empty())
  {
    size_t here = pq.top();
    pq.pop();

    cout << here + 1 << ' ';

    for (const auto there : FORWARD_ADJ[here])
    {
      REVERSE_ADJ[there].erase(REVERSE_ADJ[there].find(here));
      if (REVERSE_ADJ[there].size() == 0)
      {
        pq.emplace(there);
      }
    }
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
  cin >> N >> M;
  for (size_t it = 0; it < M; ++it)
  {
    size_t src, dst;
    cin >> src >> dst;
    FORWARD_ADJ[src - 1].insert(dst - 1);
    REVERSE_ADJ[dst - 1].insert(src - 1);
  }

  // Solve
  Solve();

  return 0;
}
