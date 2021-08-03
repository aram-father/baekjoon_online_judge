#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static const size_t kMaxN = 1000000;

size_t N;
vector<size_t> SNS[kMaxN];

bool VISIT[kMaxN];
vector<size_t> TREE[kMaxN];

size_t CACHE[kMaxN][2];

void Dfs(const size_t root)
{
  VISIT[root] = true;

  for (const auto& f : SNS[root])
  {
    if (!VISIT[f])
    {
      TREE[root].push_back(f);
      Dfs(f);
    }
  }
}

size_t Solve(const size_t root, const bool is_early_adapter)
{
  if (root >= N)
  {
    return kMaxN + 1;
  }

  size_t& ret = CACHE[root][is_early_adapter];

  if (ret != kMaxN + 1)
  {
    return ret;
  }

  if (is_early_adapter == 0)
  {
    ret = 0;
    for (const auto& f : TREE[root])
    {
      ret += Solve(f, 1);
    }
  }
  else
  {
    ret = 1;
    for (const auto& f : TREE[root])
    {
      ret += min(Solve(f, 0), Solve(f, 1));
    }
  }

  return ret;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  cin >> N;

  for (size_t it = 0; it + 1 < N; ++it)
  {
    size_t A, B;
    cin >> A >> B;
    SNS[A - 1].push_back(B - 1);
    SNS[B - 1].push_back(A - 1);
  }

  // Initialize
  for (size_t it = 0; it < N; ++it)
  {
    VISIT[it] = false;
    CACHE[it][0] = kMaxN + 1;
    CACHE[it][1] = kMaxN + 1;
  }

  Dfs(0);

  // Solve
  cout << min(Solve(0, 0), Solve(0, 1)) << "\n";

  return 0;
}
