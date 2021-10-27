#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

const int kMaxN = 100;

int N;
int BOARD[kMaxN][kMaxN];
int VISIT[kMaxN][kMaxN];

vector<vector<pair<int, int> > > ISLANDS;

void DoBfs(const int r, const int c)
{
  ISLANDS.push_back(vector<pair<int, int> >());

  queue<pair<int, int> > q;

  ISLANDS.rbegin()->emplace_back(r, c);
  VISIT[r][c] = true;
  q.emplace(r, c);

  while (!q.empty())
  {
    int cr = q.front().first;
    int cc = q.front().second;
    q.pop();

    const int dr[4] = { -1, 0, 1, 0 };
    const int dc[4] = { 0, 1, 0, -1 };

    for (int d = 0; d < 4; ++d)
    {
      int nr = cr + dr[d];
      int nc = cc + dc[d];
      if (0 > nr || nr >= N || 0 > nc || nc >= N)
      {
        continue;
      }

      if (BOARD[nr][nc] == 1 && VISIT[nr][nc] == 0)
      {
        ISLANDS.rbegin()->emplace_back(nr, nc);
        VISIT[nr][nc] = 1;
        q.emplace(nr, nc);
      }
    }
  }
}

int GetDistanceBetween(const size_t src_island, const size_t dst_island)
{
  int ret = numeric_limits<int>::max();

  for (const auto& src : ISLANDS[src_island])
  {
    for (const auto& dst : ISLANDS[dst_island])
    {
      ret = min(ret, abs(src.first - dst.first) + abs(src.second - dst.second));
    }
  }

  return ret;
}

int Solve(void)
{
  for (int r = 0; r < N; ++r)
  {
    for (int c = 0; c < N; ++c)
    {
      if (BOARD[r][c] == 1 && VISIT[r][c] == 0)
      {
        DoBfs(r, c);
      }
    }
  }

  int ret = numeric_limits<int>::max();
  for (size_t si = 0; si < ISLANDS.size(); ++si)
  {
    for (size_t di = si + 1; di < ISLANDS.size(); ++di)
    {
      ret = min(ret, GetDistanceBetween(si, di));
    }
  }

  return ret - 1;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  cin >> N;
  for (int r = 0; r < N; ++r)
  {
    for (int c = 0; c < N; ++c)
    {
      cin >> BOARD[r][c];
    }
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
