#include <cstdio>
#include <limits>
#include <algorithm>
#include <utility>

using namespace std;

const int kMaxN = 30;
const int kMaxM = 30;

const int kDr[4] = { -1, 0, 1, 0 };
const int kDc[4] = { 0, 1, 0, -1 };

typedef pair<int, int> pos_t;

class Board
{
public:
  int height_;
  int width_;
  int unvisited_count_;
  bool visit_[kMaxN][kMaxM];
  char board_[kMaxN][kMaxM];

  void ReadBoard(const int n, const int m)
  {
    height_ = n;
    width_ = m;

    unvisited_count_ = 0;
    for (int r = 0; r < height_; ++r)
    {
      scanf(" %s", board_[r]);
      for (int c = 0; c < width_; ++c)
      {
        visit_[r][c] = 0;
        unvisited_count_ += (board_[r][c] == '.') ? 1 : 0;
      }
    }
  }

  void Visit(const pos_t& pos)
  {
    --unvisited_count_;
    visit_[pos.first][pos.second] = 1;
  }

  void Unvisit(const pos_t& pos)
  {
    ++unvisited_count_;
    visit_[pos.first][pos.second] = 0;
  }

  pos_t Move(pos_t src, const int dir)
  {
    pos_t dst = src;

    while (true)
    {
      int nr = dst.first + kDr[dir];
      int nc = dst.second + kDc[dir];

      if (nr < 0 || nr >= height_ || nc < 0 || nc >= width_ || board_[nr][nc] != '.' || visit_[nr][nc] == 1)
      {
        break;
      }

      dst = pos_t(nr, nc);
      Visit(dst);
    }

    return dst;
  }

  void Rollback(const pos_t& src, const pos_t& dst, const int dir)
  {
    if (src == dst)
    {
      return;
    }

    pos_t pos = src;

    while (true)
    {
      int nr = pos.first + kDr[dir];
      int nc = pos.second + kDc[dir];
      pos = pos_t(nr, nc);
      Unvisit(pos);
      if (pos == dst)
      {
        break;
      }
    }
  }
};

int N, M;

int Simulate(const pos_t& src, const int cnt, Board& board)
{
  if (board.unvisited_count_ == 0)
  {
    return cnt;
  }

  int ret = numeric_limits<int>::max();

  for (int dir = 0; dir < 4; ++dir)
  {
    int nr = src.first + kDr[dir];
    int nc = src.second + kDc[dir];
    if (nr < 0 || nr >= board.height_ || nc < 0 || nc >= board.width_ || board.board_[nr][nc] != '.' ||
        board.visit_[nr][nc] == 1)
    {
      continue;
    }

    pos_t nsrc(nr, nc);
    board.Visit(nsrc);
    pos_t dst = board.Move(nsrc, dir);
    ret = min(ret, Simulate(dst, cnt + 1, board));
    board.Rollback(nsrc, dst, dir);
    board.Unvisit(nsrc);
  }

  return ret;
}

int main(void)
{
  int tc = 0;
  Board board;
  while (scanf(" %d %d", &N, &M) != EOF)
  {
    ++tc;
    board.ReadBoard(N, M);

    int ans = numeric_limits<int>::max();
    for (int r = 0; r < N; ++r)
    {
      for (int c = 0; c < M; ++c)
      {
        if (board.board_[r][c] != '.')
        {
          continue;
        }

        pos_t src(r, c);
        board.Visit(src);
        ans = min(ans, Simulate(src, 0, board));
        board.Unvisit(src);
      }
    }

    printf("Case %d: %d\n", tc, ans >= numeric_limits<int>::max() ? -1 : ans);
  }

  return 0;
}
