#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

// Class representing rectangle
class Rectangle
{
private:
  int lower_left_xpos_;
  int lower_left_ypos_;
  int upper_right_xpos_;
  int upper_right_ypos_;

public:
  Rectangle(void)
  {
  }
  Rectangle(const int lower_left_xpos, const int lower_left_ypos, const int upper_right_xpos,
            const int upper_right_ypos)
    : lower_left_xpos_(lower_left_xpos)
    , lower_left_ypos_(lower_left_ypos)
    , upper_right_xpos_(upper_right_xpos)
    , upper_right_ypos_(upper_right_ypos)
  {
  }

  const int lower_left_xpos(void) const
  {
    return lower_left_xpos_;
  }
  const int lower_left_ypos(void) const
  {
    return lower_left_ypos_;
  }
  const int upper_right_xpos(void) const
  {
    return upper_right_xpos_;
  }
  const int upper_right_ypos(void) const
  {
    return upper_right_ypos_;
  }
};

// Class representing lazy update
struct LazyUpdate
{
  int xpos_;
  int ypos_;
  int dp_;

  LazyUpdate(const int xpos, const int ypos, const int dp) : xpos_(xpos), ypos_(ypos), dp_(dp)
  {
  }

  bool operator<(const LazyUpdate& rhs) const
  {
    return xpos_ < rhs.xpos_;
  }

  bool operator>(const LazyUpdate& rhs) const
  {
    return xpos_ > rhs.xpos_;
  }
};

// Class representing segment tree supporting max query
class MaxTree
{
private:
  int node_[100001 * 4];

  int Update(const int root, const int left, const int right, const int update_index, const int update_value)
  {
    if (right < update_index || update_index < left)
    {
      return node_[root];
    }

    if (left == right)
    {
      return (node_[root] = update_value);
    }

    int mid = (left + right) / 2;
    int left_tree = Update(2 * root, left, mid, update_index, update_value);
    int right_tree = Update(2 * root + 1, mid + 1, right, update_index, update_value);

    return (node_[root] = max(left_tree, right_tree));
  }

  int Query(const int root, const int left, const int right, const int query_left, const int query_right)
  {
    if (right < query_left || query_right < left)
    {
      return 0;
    }

    if (query_left <= left && right <= query_right)
    {
      return node_[root];
    }

    int mid = (left + right) / 2;
    int left_tree = Query(2 * root, left, mid, query_left, query_right);
    int right_tree = Query(2 * root + 1, mid + 1, right, query_left, query_right);

    return max(left_tree, right_tree);
  }

public:
  MaxTree(void)
  {
    memset(node_, 0, sizeof(int) * 100001 * 4);
  }

  void Update(const int ypos, const int dp)
  {
    Update(1, 1, 100001, ypos + 1, dp);
  }

  int Query(const int left, const int right)
  {
    return Query(1, 1, 100001, left + 1, right + 1);
  }
};

vector<Rectangle> axis[100001];
MaxTree max_tree;

int Solve(void)
{
  priority_queue<LazyUpdate, vector<LazyUpdate>, greater<LazyUpdate> > lazy_update;

  for (int xpos = 0; xpos <= 100000; ++xpos)
  {
    while (!lazy_update.empty() && lazy_update.top().xpos_ < xpos)
    {
      int ypos = lazy_update.top().ypos_;
      int dp = lazy_update.top().dp_;
      lazy_update.pop();

      max_tree.Update(ypos, max(dp, max_tree.Query(ypos, ypos)));
    }

    for (const auto& rect : axis[xpos])
    {
      int len = max_tree.Query(0, rect.lower_left_ypos() - 1) + 1;
      lazy_update.emplace(rect.upper_right_xpos(), rect.upper_right_ypos(), len);
    }
  }

  return max_tree.Query(0, 100000);
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
  for (int it = 0; it < N; ++it)
  {
    int ll_x, ll_y, ur_x, ur_y;
    cin >> ll_x >> ll_y >> ur_x >> ur_y;
    axis[ll_x].emplace_back(ll_x, ll_y, ur_x, ur_y);
  }

  // Solve
  cout << Solve() << "\n";

  return 0;
}
