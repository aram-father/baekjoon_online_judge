#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int kMaxN = 50000;

int N;
int M;
int VISIT[kMaxN + 1];
vector<int> TREE[kMaxN + 1];

void DoBfs(const int root)
{
  queue<int> q;

  VISIT[root] = 1;
  q.emplace(root);

  while (!q.empty())
  {
    int here = q.front();
    q.pop();

    for (const auto& there : TREE[here])
    {
      if (VISIT[there] == 0)
      {
        VISIT[there] = VISIT[here] + 1;
        q.emplace(there);
      }
    }
  }
}

int FindCommonAncestor(const int a, const int b)
{
  if (VISIT[a] > VISIT[b])
  {
    return FindCommonAncestor(b, a);
  }

  int moved_a = a;
  int moved_b = b;

  // Move B till same depth with A
  if (VISIT[moved_a] != VISIT[moved_b])
  {
    while (VISIT[moved_a] != VISIT[moved_b])
    {
      for (const auto& neighbor : TREE[moved_b])
      {
        if (VISIT[neighbor] == VISIT[moved_b] - 1)
        {
          moved_b = neighbor;
          break;
        }
      }
    }
  }

  while (moved_a != moved_b)
  {
    for (const auto& neighbor : TREE[moved_a])
    {
      if (VISIT[neighbor] == VISIT[moved_a] - 1)
      {
        moved_a = neighbor;
        break;
      }
    }

    for (const auto& neighbor : TREE[moved_b])
    {
      if (VISIT[neighbor] == VISIT[moved_b] - 1)
      {
        moved_b = neighbor;
        break;
      }
    }
  }

  return moved_a;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;
  for (int i = 0; i < N - 1; ++i)
  {
    int src, dst;
    cin >> src >> dst;
    TREE[src].emplace_back(dst);
    TREE[dst].emplace_back(src);
  }

  // Build BFS Tree
  DoBfs(1);

  // Read Input
  cin >> M;
  while (M--)
  {
    int one, two;
    cin >> one >> two;

    // Solve
    cout << FindCommonAncestor(one, two) << '\n';
  }

  return 0;
}
