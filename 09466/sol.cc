#include <iostream>
#include <vector>

using namespace std;

size_t N;
vector<size_t> TABLE;

size_t VISIT_CNT;
vector<size_t> HISTORY;
vector<size_t> VISITED;
vector<bool> FINISHED;
vector<bool> IN_CYCLE;

void Dfs(const size_t vtx)
{
  VISITED[vtx] = ++VISIT_CNT;
  HISTORY[VISIT_CNT] = vtx;

  if (VISITED[TABLE[vtx]] == 0)
  {
    Dfs(TABLE[vtx]);
  }
  else if (!FINISHED[TABLE[vtx]])
  {
    for (size_t it = VISITED[TABLE[vtx]]; it <= VISITED[vtx]; ++it)
    {
      IN_CYCLE[HISTORY[it]] = true;
    }
  }

  FINISHED[vtx] = true;
}

size_t Solve(void)
{
  VISIT_CNT = 0;

  for (size_t it = 0; it < N; ++it)
  {
    if (VISITED[it] == 0)
    {
      Dfs(it);
    }
  }

  size_t sole = 0;
  for (size_t it = 0; it < N; ++it)
  {
    if (!IN_CYCLE[it])
    {
      ++sole;
    }
  }

  return sole;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  size_t tc;
  cin >> tc;

  while (tc--)
  {
    // Read input
    cin >> N;

    TABLE.assign(N, 0);

    VISITED.assign(N, 0);
    HISTORY.assign(N + 1, 0);  /// First is sentinel

    FINISHED.assign(N, false);
    IN_CYCLE.assign(N, false);

    for (size_t it = 0; it < N; ++it)
    {
      cin >> TABLE[it];
      --TABLE[it];
    }

    // Solve
    cout << Solve() << '\n';
  }

  return 0;
}
