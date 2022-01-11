#include <iostream>
#include <algorithm>
#include <cstdint>

using namespace std;

const int kMaxH = 1000;
const int kMaxW = 1000;

int H;
int W;
int A[kMaxH][kMaxW];
int R[kMaxH];
int C[kMaxW];

int64_t GetSum()
{
  int64_t ret = 0;

  for (int r = 0; r < H - 1; ++r)
  {
    for (int c = 0; c < W - 1; ++c)
    {
      ret += A[r][c] + A[r + 1][c] + A[r][c + 1] + A[r + 1][c + 1];
    }
  }

  return ret;
}

int64_t Solve()
{
  for (int r = 0; r < H; ++r)
  {
    R[r] = 0;
    for (int c = 0; c < W; ++c)
    {
      R[r] += 2 * A[r][c];
    }

    R[r] -= A[r][0] + A[r][W - 1];
  }

  for (int c = 0; c < W; ++c)
  {
    C[c] = 0;
    for (int r = 0; r < H; ++r)
    {
      C[c] += 2 * A[r][c];
    }

    C[c] -= A[0][c] + A[H - 1][c];
  }

  int64_t ans_no = GetSum();

  int64_t ans_row = ans_no;
  for (int r = 1; r < H - 1; ++r)
  {
    ans_row = max(ans_row, ans_no - R[r] + R[0]);
    ans_row = max(ans_row, ans_no - R[r] + R[H - 1]);
  }

  int64_t ans_col = ans_no;
  for (int c = 1; c < W - 1; ++c)
  {
    ans_col = max(ans_col, ans_no - C[c] + C[0]);
    ans_col = max(ans_col, ans_no - C[c] + C[W - 1]);
  }

  return max(ans_no, max(ans_col, ans_row));
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read inputs
  cin >> H >> W;
  for (int r = 0; r < H; ++r)
  {
    for (int c = 0; c < W; ++c)
    {
      cin >> A[r][c];
    }
  }

  // Solve
  cout << Solve() << '\n';

  return 0;
}
