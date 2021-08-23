#include <iostream>
#include <cstdint>

using namespace std;

int64_t fact[11];

int64_t Solve(const int64_t level, const int64_t r, const int64_t g, const int64_t b, const int64_t n)
{
  if (level > n)
  {
    return 1;
  }

  int64_t ret = 0;

  if (level % 3 == 0 && r >= level / 3 && g >= level / 3 && b >= level / 3)
  {
    int64_t cnt = fact[level] / (fact[level / 3] * fact[level / 3] * fact[level / 3]);
    cnt *= Solve(level + 1, r - level / 3, g - level / 3, b - level / 3, n);
    ret += cnt;
  }

  if (level % 2 == 0)
  {
    if (r >= level / 2 && g >= level / 2)
    {
      int64_t cnt = fact[level] / (fact[level / 2] * fact[level / 2]);
      cnt *= Solve(level + 1, r - level / 2, g - level / 2, b, n);
      ret += cnt;
    }
    if (g >= level / 2 && b >= level / 2)
    {
      int64_t cnt = fact[level] / (fact[level / 2] * fact[level / 2]);
      cnt *= Solve(level + 1, r, g - level / 2, b - level / 2, n);
      ret += cnt;
    }
    if (r >= level / 2 && b >= level / 2)
    {
      int64_t cnt = fact[level] / (fact[level / 2] * fact[level / 2]);
      cnt *= Solve(level + 1, r - level / 2, g, b - level / 2, n);
      ret += cnt;
    }
  }

  if (r >= level)
  {
    ret += Solve(level + 1, r - level, g, b, n);
  }

  if (g >= level)
  {
    ret += Solve(level + 1, r, g - level, b, n);
  }

  if (b >= level)
  {
    ret += Solve(level + 1, r, g, b - level, n);
  }

  return ret;
}

int main(void)
{
  // Preprocess
  fact[0] = 1;
  for (int64_t it = 1; it < 11; ++it)
  {
    fact[it] = fact[it - 1] * it;
  }

  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  int64_t N, R, G, B;
  cin >> N >> R >> G >> B;

  // Solve
  cout << Solve(1, R, G, B, N) << '\n';

  return 0;
}
