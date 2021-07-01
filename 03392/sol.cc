#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

static const int kMaxX = 30001;
static const int kMaxY = 30001;

class Range
{
private:
  int left_;
  int right_;

public:
  Range(void)
  {
  }

  Range(const int left, const int right) : left_(left), right_(right)
  {
  }

  const int left(void) const
  {
    return left_;
  }

  const int right(void) const
  {
    return right_;
  }

  const int length(void) const
  {
    return right_ - left_ + 1;
  }
};

class YTree
{
private:
  int length_[kMaxY * 4];
  int change_[kMaxY * 4];

public:
  YTree(void)
  {
    memset(length_, 0, sizeof(int) * kMaxY * 4);
    memset(change_, 0, sizeof(int) * kMaxY * 4);
  }

  int Query(void)
  {
    return length_[1];
  }

  void Update(const size_t root, const Range root_range, const Range update_range, const int value)
  {
    if (root_range.right() < update_range.left() || update_range.right() < root_range.left())
    {
      return;
    }

    if (update_range.left() <= root_range.left() && root_range.right() <= update_range.right())
    {
      change_[root] += value;
    }
    else
    {
      const Range left_range(root_range.left(), (root_range.left() + root_range.right()) / 2);
      const Range right_range(left_range.right() + 1, root_range.right());

      Update(2 * root, left_range, update_range, value);
      Update(2 * root + 1, right_range, update_range, value);

      // change_[root] += change_[2 * root] + change_[2 * root + 1];
    }

    if (change_[root] != 0)
    {
      length_[root] = root_range.length();
    }
    else
    {
      if (root_range.left() == root_range.right())
      {
        length_[root] = 0;
      }
      else
      {
        length_[root] = length_[2 * root] + length_[2 * root + 1];
      }
    }
  }
};

struct Edge
{
  int y_upper_;
  int y_lower_;
  int is_ending_;

  Edge(const int y_upper, const int y_lower, const int is_ending)
    : y_upper_(y_upper), y_lower_(y_lower), is_ending_(is_ending)
  {
  }
};

YTree y_tree;
vector<vector<Edge> > edges(kMaxX + 1, vector<Edge>());

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  int N;
  cin >> N;

  for (int it = 0; it < N; ++it)
  {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;

    edges[x1 + 1].emplace_back(y2, y1 + 1, 1);
    edges[x2 + 1].emplace_back(y2, y1 + 1, -1);
  }

  int total = 0;
  for (int xpos = 1; xpos < kMaxX; ++xpos)
  {
    for (const auto& edge : edges[xpos])
    {
      y_tree.Update(1, { 1, kMaxY }, { edge.y_lower_, edge.y_upper_ }, edge.is_ending_);
    }

    total += y_tree.Query();
  }

  cout << total << "\n";

  return 0;
}
