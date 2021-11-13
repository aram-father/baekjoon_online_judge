#include <iostream>
#include <utility>
#include <cmath>

using namespace std;

const int kMaxN = 10000;

int N;
pair<double, double> POINTS[kMaxN];

double Solve(void)
{
  double s = 0;

  for (int idx = 0; idx < N; ++idx)
  {
    pair<double, double> prev = POINTS[idx];
    pair<double, double> next = POINTS[(idx + 1) % N];
    pair<double, double> line(next.first - prev.first, next.second - prev.second);

    s += line.first * prev.second - line.second * prev.first;
  }

  return 0.5 * fabs(s);
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  cin >> N;
  for (int it = 0; it < N; ++it)
  {
    cin >> POINTS[it].first >> POINTS[it].second;
  }

  // Solve
  cout << fixed;
  cout.precision(1);
  cout << Solve() << '\n';

  return 0;
}
