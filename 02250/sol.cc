#include <iostream>

using namespace std;

const int kMaxN = 10000;

struct Node
{
  int size_;
  int level_;
  int position_;
  Node* left_;
  Node* right_;
};

int N;
Node NODES[kMaxN + 1];
int LEFTMOSTS[kMaxN + 1];
int RIGHTMOSTS[kMaxN + 1];
int IS_NOT_ROOT[kMaxN + 1];

int UpdateSizeAndLevel(Node* root, const int level)
{
  if (!root)
  {
    return 0;
  }

  root->level_ = level;

  root->size_ = 1;
  root->size_ += UpdateSizeAndLevel(root->left_, level + 1);
  root->size_ += UpdateSizeAndLevel(root->right_, level + 1);

  return root->size_;
}

void UpdatePosition(Node* root, const int offset)
{
  if (!root)
  {
    return;
  }

  int left_size = (root->left_ == NULL) ? 0 : root->left_->size_;

  root->position_ = offset + left_size + 1;
  UpdatePosition(root->left_, offset);
  UpdatePosition(root->right_, root->position_);
}
void Solve(const int root)
{
  // Initialize
  for (int lv = 1; lv <= N; ++lv)
  {
    LEFTMOSTS[lv] = kMaxN * kMaxN;
    RIGHTMOSTS[lv] = 0;
  }

  // Solve
  UpdateSizeAndLevel(&NODES[root], 1);
  UpdatePosition(&NODES[root], 0);

  int max_level = -1;
  for (int i = 1; i <= N; ++i)
  {
    LEFTMOSTS[NODES[i].level_] = min(LEFTMOSTS[NODES[i].level_], NODES[i].position_);
    RIGHTMOSTS[NODES[i].level_] = max(RIGHTMOSTS[NODES[i].level_], NODES[i].position_);
    max_level = max(max_level, NODES[i].level_);
  }

  int ans_level = -1;
  int ans_width = -1;

  for (int lv = 1; lv <= max_level; ++lv)
  {
    int width = RIGHTMOSTS[lv] - LEFTMOSTS[lv] + 1;
    if (width > ans_width)
    {
      ans_level = lv;
      ans_width = width;
    }
  }

  cout << ans_level << ' ' << ans_width << '\n';
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  cin >> N;
  for (int it = 0; it < N; ++it)
  {
    int parents, left, right;
    cin >> parents >> left >> right;

    NODES[parents].left_ = (left == -1) ? nullptr : &NODES[left];
    NODES[parents].right_ = (right == -1) ? nullptr : &NODES[right];

    if (left != -1)
    {
      IS_NOT_ROOT[left] = 1;
    }
    if (right != -1)
    {
      IS_NOT_ROOT[right] = 1;
    }
  }

  int root;
  for (int i = 1; i <= N; ++i)
  {
    if (IS_NOT_ROOT[i] == 0)
    {
      root = i;
      break;
    }
  }

  // Solve
  Solve(root);

  return 0;
}
