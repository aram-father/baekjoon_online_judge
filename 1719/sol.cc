#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

static const size_t kMaxDistance = 200 * 10000 + 1;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  size_t n, m;
  cin >> n >> m;

  vector<vector<size_t> > adjacent_matrix(n, vector<size_t>(n, kMaxDistance));
  vector<vector<size_t> > adjacent_matrix2(n, vector<size_t>(n, kMaxDistance));
  for (size_t u = 0; u < n; ++u)
  {
    adjacent_matrix[u][u] = 0;
    adjacent_matrix2[u][u] = 0;
  }

  for (size_t it = 0; it < m; ++it)
  {
    size_t u, v, weight;
    cin >> u >> v >> weight;
    adjacent_matrix[u - 1][v - 1] = weight;
    adjacent_matrix[v - 1][u - 1] = weight;
    adjacent_matrix2[u - 1][v - 1] = weight;
    adjacent_matrix2[v - 1][u - 1] = weight;
  }

  // Floyd-Warshall
  for (size_t mid = 0; mid < n; ++mid)
  {
    for (size_t src = 0; src < n; ++src)
    {
      for (size_t dst = 0; dst < n; ++dst)
      {
        adjacent_matrix[src][dst] =
            min(adjacent_matrix[src][dst], adjacent_matrix[src][mid] + adjacent_matrix[mid][dst]);
      }
    }
  }

  for (size_t src = 0; src < n; ++src)
  {
    for (size_t dst = 0; dst < n; ++dst)
    {
      if (src == dst)
      {
        cout << "- ";
      }
      else if (adjacent_matrix[src][dst] >= 200 * 100000 + 1)
      {
        cout << "- ";
      }
      else
      {
        size_t mid;
        for (mid = 0; mid < n; ++mid)
        {
          if (mid == src || mid == dst)
          {
            continue;
          }
          if (adjacent_matrix[src][dst] == adjacent_matrix2[src][mid] + adjacent_matrix[mid][dst])
          {
            cout << mid + 1 << ' ';
            break;
          }
        }

        if (mid == n)
        {
          cout << dst + 1 << ' ';
        }
      }
    }
    cout << "\n";
  }
  return 0;
}
