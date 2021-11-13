#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <set>

using namespace std;

const int kMaxR = 1500;
const int kMaxC = 1500;

int R, C;
string MAP[kMaxR];

int SWAN;
int VISIT[kMaxR][kMaxC];
vector<int> ICEBURGS;

const int dr[4] = { -1, 0, 1, 0 };
const int dc[4] = { 0, 1, 0, -1 };

set<int> next_iceburgs;
queue<int> q;
queue<int> boundary;

void FindSwan(void)
{
  for (int r = 0; r < R; ++r)
  {
    for (int c = 0; c < C; ++c)
    {
      if (MAP[r][c] == 'L')
      {
        SWAN = r * C + c;
        MAP[r][c] = '.';
        return;
      }
    }
  }
}

void FindIceburgs(void)
{
  for (int r = 0; r < R; ++r)
  {
    for (int c = 0; c < C; ++c)
    {
      if (MAP[r][c] == 'X')
      {
        bool will_be_melted = false;
        for (int d = 0; d < 4; ++d)
        {
          int nr = r + dr[d];
          int nc = c + dc[d];
          if (0 > nr || nr >= R || 0 > nc || nc >= C)
          {
            continue;
          }

          if (MAP[nr][nc] == 'L' || MAP[nr][nc] == '.')
          {
            will_be_melted = true;
            break;
          }
        }

        if (will_be_melted)
        {
          ICEBURGS.emplace_back(r * C + c);
        }
      }
    }
  }
}

void Melt(void)
{
  next_iceburgs.clear();

  for (const auto& iceburg : ICEBURGS)
  {
    int r = iceburg / C;
    int c = iceburg % C;

    MAP[r][c] = '.';
  }

  for (const auto& iceburg : ICEBURGS)
  {
    int r = iceburg / C;
    int c = iceburg % C;

    for (int d = 0; d < 4; ++d)
    {
      int nr = r + dr[d];
      int nc = c + dc[d];

      if (0 > nr || nr >= R || 0 > nc || nc >= C || MAP[nr][nc] != 'X')
      {
        continue;
      }

      next_iceburgs.insert(nr * C + nc);
    }
  }

  ICEBURGS.clear();

  for (const auto& iceburg : next_iceburgs)
  {
    ICEBURGS.emplace_back(iceburg);
  }
}

bool Bfs(queue<int>& boundary)
{
  while (!boundary.empty())
  {
    int r = boundary.front() / C;
    int c = boundary.front() % C;
    boundary.pop();

    VISIT[r][c] = 1;
    q.emplace(r * C + c);
  }

  while (!q.empty())
  {
    int here = q.front();
    q.pop();

    int r = here / C;
    int c = here % C;

    for (int d = 0; d < 4; ++d)
    {
      int nr = r + dr[d];
      int nc = c + dc[d];

      if (0 > nr || nr >= R || 0 > nc || nc >= C || VISIT[nr][nc] == 1)
      {
        continue;
      }

      if (VISIT[nr][nc] == 0 && MAP[nr][nc] == 'L')
      {
        return true;
      }
      else if (VISIT[nr][nc] == 0 && MAP[nr][nc] == '.')
      {
        VISIT[nr][nc] = 1;
        q.emplace(nr * C + nc);
      }
      else if (VISIT[nr][nc] == 0 && MAP[nr][nc] == 'X')
      {
        VISIT[nr][nc] = 2;
        boundary.emplace(nr * C + nc);
      }
    }
  }

  return false;
}

int Solve(void)
{
  FindSwan();
  FindIceburgs();

  boundary.emplace(SWAN);

  int day = 0;
  while (true)
  {
    if (Bfs(boundary))
    {
      break;
    }

    Melt();

    ++day;
  }

  return day;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  cin >> R >> C;
  for (int r = 0; r < R; ++r)
  {
    cin >> MAP[r];
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
