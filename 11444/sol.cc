#include <iostream>
#include <cstdint>
#include <tuple>

using namespace std;

const uint64_t kMod = 1000000007;

struct Mat
{
  uint64_t mat_[2][2];
  Mat(const uint64_t a, const uint64_t b, const uint64_t c, const uint64_t d)
  {
    mat_[0][0] = a;
    mat_[0][1] = b;
    mat_[1][0] = c;
    mat_[1][1] = d;
  }

  Mat operator*(const Mat& rhs) const
  {
    Mat ret(0, 0, 0, 0);
    for (size_t r = 0; r < 2; ++r)
    {
      for (size_t c = 0; c < 2; ++c)
      {
        for (size_t i = 0; i < 2; ++i)
        {
          ret.mat_[r][c] += mat_[r][i] * rhs.mat_[i][c];
        }

        ret.mat_[r][c] %= kMod;
      }
    }

    return ret;
  }
};

Mat GetPower(const uint64_t power)
{
  if (power == 0)
  {
    return Mat(1, 0, 0, 1);
  }

  Mat half = GetPower(power / 2);

  if (power % 2)
  {
    return Mat(1, 1, 1, 0) * half * half;
  }
  else
  {
    return half * half;
  }
}

int main(void)
{
  uint64_t n;
  cin >> n;

  Mat mat = GetPower(n - 1);

  cout << mat.mat_[0][0] << endl;

  return 0;
}
