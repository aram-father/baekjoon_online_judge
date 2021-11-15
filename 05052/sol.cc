#include <iostream>
#include <vector>
#include <string>

using namespace std;

class TrieNode
{
private:
  size_t word_count_;
  vector<TrieNode*> children_;

public:
  TrieNode(void) : word_count_(0), children_('9' - '0' + 1, nullptr)
  {
  }
  ~TrieNode(void)
  {
    for (auto& child : children_)
    {
      if (child != nullptr)
      {
        delete child;
      }
    }
  }

  void InsertWord(const string& word, const size_t index = 0)
  {
    if (index == word.size())
    {
      ++word_count_;
      return;
    }

    auto& child = children_[word[index] - '0'];
    if (child == nullptr)
    {
      child = new TrieNode();
    }
    child->InsertWord(word, index + 1);
  }

  bool hasPrefix(const string& word, const size_t index = 0)
  {
    if (index == word.size())
    {
      return !(word_count_ == 1);
    }
    if (word_count_ >= 1)
    {
      return true;
    }

    auto& child = children_[word[index] - '0'];
    {
      return child->hasPrefix(word, index + 1);
    }
  }
};

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read testcase
  int tc;
  cin >> tc;

  while (tc--)
  {
    TrieNode* root = new TrieNode();
    vector<string> words;

    int n;
    cin >> n;

    for (int it = 0; it < n; ++it)
    {
      string word;
      cin >> word;
      words.emplace_back(word);
      root->InsertWord(word);
    }

    bool is_valid = true;
    for (const auto& word : words)
    {
      if (root->hasPrefix(word))
      {
        is_valid = false;
        break;
      }
    }

    if (is_valid)
    {
      cout << "YES\n";
    }
    else
    {
      cout << "NO\n";
    }

    delete root;
  }

  return 0;
}
