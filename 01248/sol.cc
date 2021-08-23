#include <iostream>
#include <string>

using namespace std;

size_t N;
char MAT[20][20];

bool Verify(const size_t idx, const char mat[][20], int answer[])
{
  static int psum[11];

  psum[0] = 0;
  for (size_t it = 1; it <= idx; ++it)
  {
    psum[it] = psum[it - 1] + answer[it];
  }

  for (size_t it = 1; it <= idx; ++it)
  {
    for (size_t jt = it + 1; jt <= idx; ++jt)
    {
      int sum = psum[jt] - psum[it - 1];
      switch (mat[it][jt])
      {
        case '+': {
          if (sum <= 0)
          {
            return false;
          }
        }
        break;
        case '-': {
          if (sum >= 0)
          {
            return false;
          }
        }
        break;
        case '0': {
          if (sum != 0)
          {
            return false;
          }
        }
        break;
      }
    }
  }

  return true;
}

bool Solve(const size_t idx, const char mat[][20], int answer[])
{
  if (idx > N)
  {
    for (size_t it = 1; it <= N; ++it)
    {
      cout << answer[it] << ' ';
    }
    cout << '\n';

    return true;
  }

  switch (mat[idx][idx])
  {
    case '+': {
      for (int num = 1; num <= 10; ++num)
      {
        answer[idx] = num;
        if (Verify(idx, mat, answer) && Solve(idx + 1, mat, answer))
        {
          return true;
        }
      }

      return false;
    }
    break;
    case '-': {
      for (int num = -10; num <= -1; ++num)
      {
        answer[idx] = num;
        if (Verify(idx, mat, answer) && Solve(idx + 1, mat, answer))
        {
          return true;
        }
      }

      return false;
    }
    break;
    case '0': {
      answer[idx] = 0;
      return Verify(idx, mat, answer) && Solve(idx + 1, mat, answer);
    }
    break;
  }

  return false;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Input
  string mat;
  cin >> N >> mat;

  size_t idx = 0;
  for (size_t it = 1; it <= N; ++it)
  {
    for (size_t jt = it; jt <= N; ++jt)
    {
      MAT[it][jt] = mat[idx++];
    }
  }

  // Solve
  int ANSWER[20];
  Solve(1, MAT, ANSWER);

  return 0;
}
