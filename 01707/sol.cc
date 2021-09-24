#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

size_t K;
size_t V, E;
vector<vector<int> > G;

bool Color(const size_t here, const size_t color, vector<size_t>& colors)
{
  colors[here] = color;

  for (const auto there : G[here])
  {
    if (colors[there] == 0)
    {
      if (!Color(there, (colors[here] == 1) ? 2 : 1, colors))
      {
        return false;
      }
    }
    else if (colors[there] == colors[here])
    {
      return false;
    }
  }

  return true;
}

string Solve(void)
{
  vector<size_t> colors(V, 0);

  for (size_t it = 0; it < V; ++it)
  {
    if (colors[it] == 0 && !Color(it, 1, colors))
    {
      return "NO";
    }
  }

  return "YES";
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  cin >> K;

  while (K--)
  {
    // Read Inputs
    cin >> V >> E;
    G.assign(V, vector<int>());

    for (size_t it = 0; it < E; ++it)
    {
      size_t src, dst;
      cin >> src >> dst;

      G[src - 1].emplace_back(dst - 1);
      G[dst - 1].emplace_back(src - 1);
    }

    // Solve
    cout << Solve() << '\n';
  }

  return 0;
}
