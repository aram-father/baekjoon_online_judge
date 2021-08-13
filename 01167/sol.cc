#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int kMaxV = 100000;

int V;

vector<pair<int, int> > AL[kMaxV];

vector<bool> VISIT_1ST(kMaxV, false);
vector<bool> VISIT_2ND(kMaxV, false);
vector<bool> VISIT_3RD(kMaxV, false);

vector<int> DIST_1ST(kMaxV, 0);
vector<int> DIST_2ND(kMaxV, 0);
vector<int> DIST_3RD(kMaxV, 0);

void Path(const int here, vector<bool>& visit, vector<int>& dist)
{
  visit[here] = true;

  for (const auto& neighbor : AL[here])
  {
    const int there = neighbor.second;
    const int weight = neighbor.first;

    if (!visit[there])
    {
      dist[there] = dist[here] + weight;
      Path(there, visit, dist);
    }
  }
}

int Solve(void)
{
  Path(0, VISIT_1ST, DIST_1ST);

  int far_vtx = 0;
  int far_dist = DIST_1ST[far_vtx];

  for (int v = 0; v < V; ++v)
  {
    if (DIST_1ST[v] > far_dist)
    {
      far_vtx = v;
      far_dist = DIST_1ST[v];
    }
  }

  Path(far_vtx, VISIT_2ND, DIST_2ND);

  int far_vtx_2 = far_vtx;
  int far_dist_2 = DIST_2ND[far_vtx_2];

  for (int v = 0; v < V; ++v)
  {
    if (DIST_2ND[v] > far_dist_2)
    {
      far_vtx_2 = v;
      far_dist_2 = DIST_2ND[v];
    }
  }

  Path(far_vtx_2, VISIT_3RD, DIST_3RD);

  return DIST_3RD[far_vtx];
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> V;
  for (int it = 0; it < V; ++it)
  {
    int src;
    cin >> src;

    while (true)
    {
      int dst, weight;
      cin >> dst;

      if (dst == -1)
      {
        break;
      }

      cin >> weight;

      AL[src - 1].emplace_back(weight, dst - 1);
    }
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
