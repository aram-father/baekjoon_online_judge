#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int kMaxN = 125;
const int kMaxK = 9;

int N;
int BOARD[kMaxN][kMaxN];

int Solve(void)
{
  const int kDr[4] = { -1, 0, 1, 0 };
  const int kDc[4] = { 0, 1, 0, -1 };

  vector<bool> is_queued(N * N, false);
  vector<int> distances(N * N, kMaxN * kMaxN * kMaxK + 1);

  queue<int> q;

  is_queued[0] = true;
  distances[0] = 0;
  q.push(0);

  while (!q.empty())
  {
    int row = q.front() / N;
    int col = q.front() % N;
    q.pop();

    const int kHere = row * N + col;

    is_queued[kHere] = false;

    for (size_t d = 0; d < 4; ++d)
    {
      int nrow = row + kDr[d];
      int ncol = col + kDc[d];

      if (nrow < 0 || nrow >= N || ncol < 0 || ncol >= N)
      {
        continue;
      }

      int there = nrow * N + ncol;

      if (distances[there] > distances[kHere] + BOARD[nrow][ncol])
      {
        distances[there] = distances[kHere] + BOARD[nrow][ncol];
        if (!is_queued[there])
        {
          is_queued[there] = true;
          q.push(there);
        }
      }
    }
  }

  return BOARD[0][0] + distances[N * N - 1];
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int tc = 0;
  while (++tc)
  {
    cin >> N;

    if (N == 0)
    {
      break;
    }

    for (int row = 0; row < N; ++row)
    {
      for (int col = 0; col < N; ++col)
      {
        cin >> BOARD[row][col];
      }
    }

    cout << "Problem " << tc << ": " << Solve() << "\n";
  }

  return 0;
}
