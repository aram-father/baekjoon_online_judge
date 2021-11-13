#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Number
{
private:
  string number_;

public:
  Number(void) = default;
  Number& operator=(const Number& rhs) = default;

  explicit Number(const string& number) : number_(number)
  {
  }

  const std::string& number(void) const
  {
    return number_;
  }

  Number operator+(const Number& rhs) const
  {
    string result;

    size_t length = max(number().size(), rhs.number().size());

    size_t sum;
    size_t carry = 0;
    for (size_t digit = 0; digit < length; ++digit)
    {
      char digit_a = (number().size() >= digit + 1) ? number()[number().size() - digit - 1] : '0';
      char digit_b = (rhs.number().size() >= digit + 1) ? rhs.number()[rhs.number().size() - digit - 1] : '0';

      sum = ((digit_a - '0') + (digit_b - '0') + carry) % 10;
      carry = ((digit_a - '0') + (digit_b - '0') + carry) / 10;

      result += string(1, static_cast<char>(sum + '0'));
    }

    if (carry)
    {
      result += string(1, static_cast<char>(carry + '0'));
    }

    reverse(result.begin(), result.end());
    return Number(result);
  }
};

const int kMaxN = 10000;
Number CACHE[kMaxN + 1][2];

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Preprocessing
  CACHE[3][0] = Number("3");
  CACHE[3][1] = Number("4");
  CACHE[4][0] = Number("5");
  CACHE[4][1] = Number("7");

  for (int n = 5; n <= kMaxN; ++n)
  {
    CACHE[n][0] = CACHE[n - 1][0] + CACHE[n - 2][0];
    CACHE[n][1] = CACHE[n - 1][0] + CACHE[n - 2][0] + CACHE[n - 2][0];
  }

  // Solve
  int N;
  while (cin >> N)
  {
    cout << CACHE[N][1].number() << '\n';
  }

  return 0;
}
