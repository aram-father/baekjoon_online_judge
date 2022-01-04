#include <cstdio>
#include <algorithm>

using namespace std;

const int kMaxH = 4;
const int kMaxW = 4;

int H;
int W;
int PAPER[kMaxH][kMaxW];
int VISIT[kMaxH][kMaxW];

int Assemble(const int row, const int col, const int height, const int width)
{
  int ret = 0;

  for (int h = 0; h < height; ++h)
  {
    for (int w = 0; w < width; ++w)
    {
      ret *= 10;
      ret += PAPER[row + h][col + w];
    }
  }

  return ret;
}

int Solve(const int row, const int col)
{
  const int index = row * W + col;

  if (index >= H * W)
  {
    return 0;
  }

  if (VISIT[row][col])
  {
    return Solve((index + 1) / W, (index + 1) % W);
  }

  int ret = 0;

  // Sole
  VISIT[row][col] = 1;
  ret = max(ret, Assemble(row, col, 1, 1) + Solve((index + 1) / W, (index + 1) % W));
  VISIT[row][col] = 0;

  // Vertical
  for (int h = 2; row + h - 1 < H && VISIT[row + h - 1][col] == 0; ++h)
  {
    for (int hh = 0; hh < h; ++hh)
    {
      VISIT[row + hh][col] = 1;
    }

    ret = max(ret, Assemble(row, col, h, 1) + Solve((index + 1) / W, (index + 1) % W));

    for (int hh = 0; hh < h; ++hh)
    {
      VISIT[row + hh][col] = 0;
    }
  }

  // Horizontal
  for (int w = 2; col + w - 1 < W && VISIT[row][col + w - 1] == 0; ++w)
  {
    for (int ww = 0; ww < w; ++ww)
    {
      VISIT[row][col + ww] = 1;
    }

    ret = max(ret, Assemble(row, col, 1, w) + Solve((index + 1) / W, (index + 1) % W));

    for (int ww = 0; ww < w; ++ww)
    {
      VISIT[row][col + ww] = 0;
    }
  }

  return ret;
}

int main(void)
{
  // Read Input
  scanf(" %d %d", &H, &W);
  for (int r = 0; r < H; ++r)
  {
    for (int c = 0; c < W; ++c)
    {
      scanf(" %1d", &PAPER[r][c]);
    }
  }

  // Solve
  printf("%d\n", Solve(0, 0));

  return 0;
}
