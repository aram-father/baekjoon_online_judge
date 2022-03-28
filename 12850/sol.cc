#include <cstdio>
#include <cstdint>

const int64_t kMod = 1000000007;

int64_t D;
int64_t M[8][8] = { { 0, 1, 1, 0, 0, 0, 0, 0 }, { 1, 0, 1, 1, 0, 0, 0, 0 }, { 1, 1, 0, 1, 1, 0, 0, 0 },
                    { 0, 1, 1, 0, 1, 1, 0, 0 }, { 0, 0, 1, 1, 0, 1, 1, 0 }, { 0, 0, 0, 1, 1, 0, 0, 1 },
                    { 0, 0, 0, 0, 1, 0, 0, 1 }, { 0, 0, 0, 0, 0, 1, 1, 0 } };

void Power(int64_t m[][8], const int64_t k)
{
  if (k == 1)
  {
    for (int64_t i = 0; i < 8; ++i)
    {
      for (int64_t j = 0; j < 8; ++j)
      {
        m[i][j] = M[i][j];
      }
    }

    return;
  }

  int64_t half[8][8];
  int64_t full[8][8];
  Power(half, k / 2);

  for (int64_t r = 0; r < 8; ++r)
  {
    for (int64_t c = 0; c < 8; ++c)
    {
      full[r][c] = 0;
      for (int64_t k = 0; k < 8; ++k)
      {
        full[r][c] += half[r][k] * half[k][c];
        full[r][c] %= kMod;
      }
    }
  }

  if (k % 2)
  {
    for (int64_t r = 0; r < 8; ++r)
    {
      for (int64_t c = 0; c < 8; ++c)
      {
        m[r][c] = 0;
        for (int64_t k = 0; k < 8; ++k)
        {
          m[r][c] += full[r][k] * M[k][c];
          m[r][c] %= kMod;
        }
      }
    }
  }
  else
  {
    for (int64_t r = 0; r < 8; ++r)
    {
      for (int64_t c = 0; c < 8; ++c)
      {
        m[r][c] = full[r][c];
      }
    }
  }

  return;
}

int main(void)
{
  scanf(" %ld", &D);

  int64_t ret[8][8];
  Power(ret, D);

  /*
  int64_t answer = 0;
  for (int64_t k = 0; k < 8; ++k)
  {
    answer += ret[k][0];
    answer %= kMod;
  }
  */

  printf("%ld\n", ret[0][0]);

  return 0;
}
