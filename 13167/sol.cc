#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdint>
#include <map>

using namespace std;

static const int kMaxX = 5000 * 2;
static const int kMaxY = 5000 * 2;

class Poster
{
public:
  static int i2x[kMaxX];
  static int i2y[kMaxY];

  int ll_x_, ll_y_;
  int ur_x_, ur_y_;

  int ll_x_idx_, ll_y_idx_;
  int ur_x_idx_, ur_y_idx_;

  Poster(const int ll_x, const int ll_y, const int ur_x, const int ur_y)
    : ll_x_(ll_x), ll_y_(ll_y), ur_x_(ur_x), ur_y_(ur_y)
  {
  }
};

int Poster::i2x[kMaxX];
int Poster::i2y[kMaxY];

class DisjointSet
{
private:
  int parents_[kMaxY];
  bool is_set_[kMaxY];

public:
  void Initialize(void)
  {
    for (int it = 0; it < kMaxY; ++it)
    {
      parents_[it] = it;
      is_set_[it] = false;
    }
  }

  int Find(const int y)
  {
    if (parents_[y] == y)
    {
      return y;
    }

    return (parents_[y] = Find(parents_[y]));
  }

  void Union(const int lower, const int upper)
  {
    is_set_[lower] = true;
    is_set_[upper] = true;

    int lower_parents = Find(lower);
    int upper_parents = Find(upper);

    parents_[min(lower_parents, upper_parents)] = max(lower_parents, upper_parents);
  }

  bool IsSet(const int y)
  {
    return is_set_[y];
  }
};

void Codec(vector<Poster>& posters)
{
  map<int, int> x_enc;
  map<int, int> y_enc;

  for (const auto& poster : posters)
  {
    x_enc[poster.ll_x_] = 0;
    x_enc[poster.ur_x_] = 0;
    y_enc[poster.ll_y_] = 0;
    y_enc[poster.ur_y_] = 0;
  }

  int idx;

  idx = 0;
  for (auto& x : x_enc)
  {
    x.second = idx;
    Poster::i2x[idx] = x.first;
    ++idx;
  }

  idx = 0;
  for (auto& y : y_enc)
  {
    y.second = idx;
    Poster::i2y[idx] = y.first;
    ++idx;
  }

  for (auto& poster : posters)
  {
    poster.ll_x_idx_ = x_enc[poster.ll_x_];
    poster.ll_y_idx_ = y_enc[poster.ll_y_];
    poster.ur_x_idx_ = x_enc[poster.ur_x_];
    poster.ur_y_idx_ = y_enc[poster.ur_y_];
  }
}

void Solve(vector<Poster>& posters)
{
  vector<uint64_t> areas(posters.size(), 0);

  DisjointSet disjoint_set;

  for (int x_idx = 0; x_idx < kMaxX; ++x_idx)
  {
    disjoint_set.Initialize();

    for (int it = posters.size() - 1; it >= 0; --it)
    {
      if (posters[it].ll_x_idx_ <= x_idx && x_idx < posters[it].ur_x_idx_)
      {
        int y_idx = posters[it].ll_y_idx_;

        while (y_idx < posters[it].ur_y_idx_)
        {
          if (!disjoint_set.IsSet(y_idx))
          {
            areas[it] += static_cast<int64_t>(Poster::i2x[x_idx + 1] - Poster::i2x[x_idx]) *
                         (Poster::i2y[y_idx + 1] - Poster::i2y[y_idx]);
            disjoint_set.Union(posters[it].ll_y_idx_, y_idx++);
          }
          else
          {
            y_idx = disjoint_set.Find(y_idx) + 1;
          }
        }
      }
    }
  }

  for (const auto& area : areas)
  {
    cout << area << "\n";
  }
}

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  int N;
  cin >> N;

  vector<Poster> posters;
  for (int it = 0; it < N; ++it)
  {
    int ll_x, ll_y, ur_x, ur_y;
    cin >> ll_x >> ll_y >> ur_x >> ur_y;
    posters.emplace_back(ll_x, ll_y, ur_x, ur_y);
  }

  Codec(posters);

  Solve(posters);

  return 0;
}
