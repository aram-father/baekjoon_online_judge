#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

const int kMaxH = 100;
const int kMaxW = 100;

int H;
int W;
vector<string> BOARD;
vector<bool> KEYS;

void OpenDoors()
{
  for (int r = 0; r < H; ++r)
  {
    for (int c = 0; c < W; ++c)
    {
      if ('A' <= BOARD[r][c] && BOARD[r][c] <= 'Z' && KEYS[BOARD[r][c] - 'A'])
      {
        BOARD[r][c] = '.';
      }
    }
  }
}

inline bool IsVisitable(const int r, const int c)
{
  return (BOARD[r][c] == '.' || BOARD[r][c] == '$' || ('a' <= BOARD[r][c] && BOARD[r][c] <= 'z'));
}

pair<int, int> BfsOnce()
{
  OpenDoors();

  vector<vector<bool> > visited(H, vector<bool>(W, false));
  queue<pair<int, int> > q;

  for (int r = 0; r < H; ++r)
  {
    if (IsVisitable(r, 0))
    {
      visited[r][0] = true;
      q.emplace(r, 0);
    }
    if (IsVisitable(r, W - 1))
    {
      visited[r][W - 1] = true;
      q.emplace(r, W - 1);
    }
  }

  for (int c = 0; c < W; ++c)
  {
    if (IsVisitable(0, c))
    {
      visited[0][c] = true;
      q.emplace(0, c);
    }
    if (IsVisitable(H - 1, c))
    {
      visited[H - 1][c] = true;
      q.emplace(H - 1, c);
    }
  }

  pair<int, int> ret(0, 0);

  while (!q.empty())
  {
    int r = q.front().first;
    int c = q.front().second;
    q.pop();

    if (BOARD[r][c] == '$')
    {
      ++ret.first;
      BOARD[r][c] = '.';
    }
    else if ('a' <= BOARD[r][c] && BOARD[r][c] <= 'z')
    {
      if (!KEYS[BOARD[r][c] - 'a'])
      {
        ++ret.second;
        KEYS[BOARD[r][c] - 'a'] = true;
        BOARD[r][c] = '.';
      }
    }

    const int dr[4] = { -1, 0, 1, 0 };
    const int dc[4] = { 0, 1, 0, -1 };

    for (int dir = 0; dir < 4; ++dir)
    {
      int nr = r + dr[dir];
      int nc = c + dc[dir];
      if (0 > nr || nr >= H || 0 > nc || nc >= W)
      {
        continue;
      }
      if (!visited[nr][nc] && IsVisitable(nr, nc))
      {
        visited[nr][nc] = true;
        q.emplace(nr, nc);
      }
    }
  }

  return ret;
}

int Solve()
{
  int answer = 0;
  while (true)
  {
    auto ret = BfsOnce();
    if (ret.first == 0 && ret.second == 0)
    {
      break;
    }

    answer += ret.first;
  }

  return answer;
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int testcase;
  cin >> testcase;

  while (testcase--)
  {
    // Read input
    cin >> H >> W;
    BOARD.assign(H, "");
    KEYS.assign(26, false);
    for (int r = 0; r < H; ++r)
    {
      cin >> BOARD[r];
    }

    string keys;
    cin >> keys;
    if (keys.compare("0") != 0)
    {
      for (auto ch : keys)
      {
        KEYS[ch - 'a'] = true;
      }
    }

    // Solve
    cout << Solve() << '\n';
  }

  return 0;
}
