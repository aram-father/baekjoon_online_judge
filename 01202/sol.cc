#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdint>

using namespace std;

class Gem
{
private:
  int weight_;
  int price_;

public:
  Gem(void)
  {
  }
  Gem(const int weight, const int price) : weight_(weight), price_(price)
  {
  }

  const int weight(void) const
  {
    return weight_;
  }

  const int price(void) const
  {
    return price_;
  }

  static bool CompareWeight(const Gem& lhs, const Gem& rhs)
  {
    return lhs.weight() < rhs.weight();
  }

  bool operator<(const Gem& rhs) const
  {
    return price_ < rhs.price();
  }
};

class Bag
{
private:
  int capacity_;

public:
  Bag(void)
  {
  }
  Bag(const int capacity) : capacity_(capacity)
  {
  }

  const int capacity(void) const
  {
    return capacity_;
  }

  bool operator<(const Bag& rhs) const
  {
    return capacity_ < rhs.capacity();
  }
};

int64_t Solve(vector<Gem>& gems, vector<Bag>& bags)
{
  sort(gems.begin(), gems.end(), Gem::CompareWeight);
  sort(bags.begin(), bags.end());

  priority_queue<Gem> pq;

  int64_t ret = 0;
  size_t gem_idx = 0;
  for (const auto& bag : bags)
  {
    while (gem_idx < gems.size())
    {
      if (bag.capacity() >= gems[gem_idx].weight())
      {
        pq.emplace(gems[gem_idx]);
        ++gem_idx;
      }
      else
      {
        break;
      }
    }

    if (!pq.empty())
    {
      ret += pq.top().price();
      pq.pop();
    }
  }

  return ret;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  int n, k;
  cin >> n >> k;

  vector<Gem> gems;
  for (int it = 0; it < n; ++it)
  {
    int weight, price;
    cin >> weight >> price;

    gems.emplace_back(weight, price);
  }

  vector<Bag> bags;
  for (int it = 0; it < k; ++it)
  {
    int capacity;
    cin >> capacity;
    bags.emplace_back(capacity);
  }

  // Solve
  cout << Solve(gems, bags) << '\n';

  return 0;
}
