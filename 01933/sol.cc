#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const size_t kMaxN = 100000;

struct Edge
{
  size_t xpos_;
  size_t height_;
  size_t bldg_no_;
  bool is_opening_;

  Edge(const size_t xpos, const size_t height, const size_t bldg_no, const bool is_opening)
    : xpos_(xpos), height_(height), bldg_no_(bldg_no), is_opening_(is_opening)
  {
  }

  bool operator<(const Edge& rhs) const
  {
    return xpos_ < rhs.xpos_;
  }
};

size_t N;
vector<Edge> EDGES;

void Solve(void)
{
  sort(EDGES.begin(), EDGES.end());

  size_t prev_height = 0;
  set<pair<size_t, size_t> > pool;

  size_t edge_no = 0;
  while (edge_no < EDGES.size())
  {
    const auto& edge = EDGES[edge_no];
    if (edge.is_opening_)
    {
      pool.emplace(edge.height_, edge.bldg_no_);
    }
    else
    {
      auto it = pool.find(pair<size_t, size_t>(edge.height_, edge.bldg_no_));
      pool.erase(it);
    }

    if (edge_no + 1 == EDGES.size())
    {
      cout << edge.xpos_ << ' ' << 0 << ' ';
    }
    else if (edge.xpos_ != EDGES[edge_no + 1].xpos_)
    {
      if (pool.empty())
      {
        cout << edge.xpos_ << ' ' << 0 << ' ';
      }
      else
      {
        size_t height = pool.rbegin()->first;
        if (prev_height != height)
        {
          cout << edge.xpos_ << ' ' << height << ' ';
          prev_height = height;
        }
      }
    }

    ++edge_no;
  }

  cout << '\n';
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;

  for (size_t it = 0; it < N; ++it)
  {
    size_t l, h, r;
    cin >> l >> h >> r;
    EDGES.emplace_back(l, h, it, true);
    EDGES.emplace_back(r, h, it, false);
  }

  // Solve
  Solve();

  return 0;
}
