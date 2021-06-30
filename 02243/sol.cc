#include <iostream>
#include <cstdlib>

using namespace std;

class Candy
{
public:
  int taste_;
  int quantity_;

  int priority_;
  int size_;

  Candy* left_;
  Candy* right_;

  Candy(const int taste, const int quantity)
    : taste_(taste), quantity_(quantity), priority_(rand()), size_(quantity), left_(nullptr), right_(nullptr)
  {
  }

  void SetLeft(Candy* left)
  {
    left_ = left;
    CalculateSize();
  }

  void SetRight(Candy* right)
  {
    right_ = right;
    CalculateSize();
  }

  void CalculateSize(void)
  {
    size_ = quantity_;
    size_ += (left_ == nullptr) ? 0 : left_->size_;
    size_ += (right_ == nullptr) ? 0 : right_->size_;
  }
};

class Meap
{
public:
  static pair<Candy*, Candy*> Split(Candy* root, int taste)
  {
    if (root == nullptr)
    {
      return pair<Candy*, Candy*>(nullptr, nullptr);
    }

    pair<Candy*, Candy*> splited;
    if (root->taste_ < taste)
    {
      splited = Split(root->right_, taste);
      root->SetRight(splited.first);
      return pair<Candy*, Candy*>(root, splited.second);
    }
    else
    {
      splited = Split(root->left_, taste);
      root->SetLeft(splited.second);
      return pair<Candy*, Candy*>(splited.first, root);
    }
  }

  static Candy* Insert(Candy* root, Candy* node)
  {
    if (root == nullptr)
    {
      return node;
    }

    if (root->priority_ > node->priority_)
    {
      if (node->taste_ < root->taste_)
      {
        root->SetLeft(Insert(root->left_, node));
      }
      else
      {
        root->SetRight(Insert(root->right_, node));
      }

      return root;
    }
    else
    {
      pair<Candy*, Candy*> splited = Split(root, node->taste_);
      node->SetLeft(splited.first);
      node->SetRight(splited.second);
      return node;
    }
  }

  static Candy* Merge(Candy* a, Candy* b)
  {
    if (a == nullptr)
    {
      return b;
    }
    if (b == nullptr)
    {
      return a;
    }

    if (a->priority_ > b->priority_)
    {
      a->SetRight(Merge(a->right_, b));
      return a;
    }
    else
    {
      b->SetLeft(Merge(a, b->left_));
      return b;
    }
  }

  static Candy* Erase(Candy* root, int taste)
  {
    if (root == nullptr)
    {
      return nullptr;
    }

    if (root->taste_ == taste)
    {
      auto ret = Merge(root->left_, root->right_);
      delete root;
      return ret;
    }
    else if (taste < root->taste_)
    {
      root->SetLeft(Erase(root->left_, taste));
      return root;
    }
    else
    {
      root->SetRight(Erase(root->right_, taste));
      return root;
    }
  }

  static Candy* Find(Candy* root, int taste)
  {
    if (root == nullptr)
    {
      return nullptr;
    }

    if (root->taste_ == taste)
    {
      return root;
    }
    else if (taste < root->taste_)
    {
      return Find(root->left_, taste);
    }
    else
    {
      return Find(root->right_, taste);
    }
  }

  static Candy* Update(Candy* root, int taste, const int diff)
  {
    if (root == nullptr)
    {
      return nullptr;
    }

    if (root->taste_ == taste)
    {
      root->quantity_ += diff;
      root->CalculateSize();

      if (root->quantity_ == 0)
      {
        return Erase(root, taste);
      }
      else
      {
        return root;
      }
    }
    else if (taste < root->taste_)
    {
      root->SetLeft(Update(root->left_, taste, diff));
      return root;
    }
    else
    {
      root->SetRight(Update(root->right_, taste, diff));
      return root;
    }
  }

  static Candy* GetNth(Candy* root, int n_th)
  {
    if (root == nullptr)
    {
      return nullptr;
    }

    int prev = (root->left_) ? root->left_->size_ : 0;

    if (prev + 1 <= n_th && n_th <= prev + root->quantity_)
    {
      return root;
    }
    else if (n_th <= prev)
    {
      return GetNth(root->left_, n_th);
    }
    else
    {
      return GetNth(root->right_, n_th - prev - root->quantity_);
    }
  }
};

class CandyBox
{
public:
  Candy* root_;

  CandyBox(void) : root_(nullptr)
  {
  }

  void PutOrTake(const int taste, const int diff)
  {
    if (Meap::Find(root_, taste) == nullptr && diff > 0)
    {
      root_ = Meap::Insert(root_, new Candy(taste, diff));
      return;
    }

    root_ = Meap::Update(root_, taste, diff);
  }

  int GetNth(const int n_th)
  {
    int taste = Meap::GetNth(root_, n_th)->taste_;
    PutOrTake(taste, -1);
    return taste;
  }

  void Traverse(Candy* root)
  {
    if (root == nullptr)
    {
      cout << endl;
      return;
    }

    cout << root->taste_ << " / " << root->quantity_ << " / " << root->size_ << "\n";
    cout << "\tleft : ";
    Traverse(root->left_);
    cout << "\tright : ";
    Traverse(root->right_);
  }
};

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Solve
  int N;
  cin >> N;

  CandyBox candy_box;

  while (N--)
  {
    int A, B, C;

    cin >> A;

    if (A == 1)
    {
      cin >> B;
      cout << candy_box.GetNth(B) << "\n";
    }
    else
    {
      cin >> B >> C;
      candy_box.PutOrTake(B, C);
    }

    // candy_box.Traverse(candy_box.root_);
  }

  return 0;
}
