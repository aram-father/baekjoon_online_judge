#include <iostream>
#include <cstdint>

using namespace std;

const int kMod = 1000000;

int64_t N;

struct Mat2x2
{
  int64_t mat[2][2];
  Mat2x2(const int64_t a, const int64_t b, const int64_t c, const int64_t d)
  {
    mat[0][0] = a;
    mat[0][1] = b;
    mat[1][0] = c;
    mat[1][1] = d;
  }
  Mat2x2 operator*(const Mat2x2& rhs)
  {
    Mat2x2 ret(0, 0, 0, 0);
    for (size_t r = 0; r < 2; ++r)
    {
      for (size_t c = 0; c < 2; ++c)
      {
        for (size_t i = 0; i < 2; ++i)
        {
          ret.mat[r][c] += mat[r][i] * rhs.mat[i][c];
          ret.mat[r][c] %= kMod;
        }
      }
    }
    return ret;
  }
};

Mat2x2 Power(const int64_t n)
{
  if (n == 0)
  {
    return Mat2x2(1, 0, 0, 1);
  }

  Mat2x2 half = Power(n / 2);

  if (n % 2)
  {
    return Mat2x2(1, 1, 1, 0) * half * half;
  }
  else
  {
    return half * half;
  }
}

int64_t Solve(const int64_t n)
{
  if (n == 0)
  {
    return 0;
  }

  if (n == 1)
  {
    return 1;
  }

  Mat2x2 mat = Power(n);

  return mat.mat[1][0];
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  cin >> N;

  // Solve
  cout << Solve(N) << '\n';

  return 0;
}
