#include <iostream>
#include <vector>

using namespace std;

const int kMaxN = 32000;
const int kMaxM = 100000;

int N;
int M;

bool VISIT[kMaxN + 1];
vector<int> ADJ[kMaxN + 1];

void DoDfs(const int here, vector<int>& answer)
{
  VISIT[here] = true;
  for (const auto& there : ADJ[here])
  {
    if (!VISIT[there])
    {
      DoDfs(there, answer);
    }
  }

  answer.emplace_back(here);
}

void Solve(void)
{
  vector<int> answer;

  for (int idx = 1; idx <= N; ++idx)
  {
    ADJ[0].emplace_back(idx);
  }

  DoDfs(0, answer);

  for (auto it = answer.rbegin() + 1; it != answer.rend(); ++it)
  {
    cout << *it << ' ';
  }

  cout << '\n';

  return;
}

int main(void)
{
  // For Faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read Inputs
  cin >> N >> M;
  for (int it = 0; it < M; ++it)
  {
    int src, dst;
    cin >> src >> dst;
    ADJ[src].emplace_back(dst);
  }

  // Solve
  Solve();

  return 0;
}
