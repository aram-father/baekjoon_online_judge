#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int kMaxLayers = 20;

int N;
int K;

struct Node
{
  int number;
  int position;
  Node* left;
  Node* right;
};

Node* Insert(Node** root, const int number, const int position = 1)
{
  if (*root == nullptr)
  {
    *root = new Node();
    (*root)->number = number;
    (*root)->position = position;
    (*root)->left = nullptr;
    (*root)->right = nullptr;
  }
  else
  {
    if ((*root)->number > number)
    {
      (*root)->left = Insert(&((*root)->left), number, (*root)->position * 2);
    }
    else
    {
      (*root)->right = Insert(&((*root)->right), number, (*root)->position * 2 + 1);
    }
  }

  return *root;
}

void DeleteTree(Node* root)
{
  if (root == nullptr)
  {
    return;
  }

  DeleteTree(root->left);
  DeleteTree(root->right);
}

void Traverse(Node* root, set<int>& positions)
{
  if (root == nullptr)
  {
    return;
  }

  positions.insert(root->position);
  Traverse(root->left, positions);
  Traverse(root->right, positions);
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N >> K;

  vector<Node*> trees(N, nullptr);
  for (int it = 0; it < N; ++it)
  {
    for (int jt = 0; jt < K; ++jt)
    {
      int layer;
      cin >> layer;
      trees[it] = Insert(&trees[it], layer);
    }
  }

  // Solve
  set<set<int> > shapes;
  for (int it = 0; it < N; ++it)
  {
    set<int> shape;
    Traverse(trees[it], shape);
    shapes.insert(shape);
  }

  cout << shapes.size() << '\n';

  for (int it = 0; it < N; ++it)
  {
    DeleteTree(trees[it]);
  }

  return 0;
}
