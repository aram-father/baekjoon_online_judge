#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

const int kMaxN = 100;
const int kMaxElem = 200;

int N;
int ARR[kMaxN][kMaxN];

bool Bfs(const int min, const int max)
{
  if (min > ARR[0][0] || ARR[0][0] > max || min > ARR[N - 1][N - 1] || ARR[N - 1][N - 1] > max)
  {
    return false;
  }

  vector<bool> visited(N * N, false);
  queue<int> q;

  const int dr[4] = { -1, 0, 1, 0 };
  const int dc[4] = { 0, 1, 0, -1 };

  visited[0] = true;
  q.push(0);

  while (!q.empty())
  {
    int r = q.front() / N;
    int c = q.front() % N;
    q.pop();

    if (r + 1 == N && c + 1 == N)
    {
      return true;
    }

    for (int d = 0; d < 4; ++d)
    {
      int nr = r + dr[d];
      int nc = c + dc[d];
      int nidx = nr * N + nc;

      if (0 > nr || nr >= N || 0 > nc || nc >= N)
      {
        continue;
      }

      if (min <= ARR[nr][nc] && ARR[nr][nc] <= max && !visited[nidx])
      {
        visited[nidx] = true;
        q.push(nidx);
      }
    }
  }

  return false;
}

int Solve(void)
{
  int left = 0;
  int right = kMaxElem;

  while (left < right)
  {
    int mid = (left + right) / 2;

    bool possible = false;
    for (int min = 0; min + mid <= kMaxElem; ++min)
    {
      if (Bfs(min, min + mid))
      {
        possible = true;
        break;
      }
    }

    if (possible)
    {
      right = mid;
    }
    else
    {
      left = mid + 1;
    }
  }

  return left;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;
  for (int r = 0; r < N; ++r)
  {
    for (int c = 0; c < N; ++c)
    {
      cin >> ARR[r][c];
    }
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
