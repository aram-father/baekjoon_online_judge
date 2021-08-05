#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main(void)
{
  // For faster IO
  ios_base::sync_with_stdio(false);
  cout.tie(nullptr);
  cin.tie(nullptr);

  // Read input
  size_t N;
  cin >> N;

  vector<size_t> STUDENTS(N, 0);
  for (auto& student : STUDENTS)
  {
    cin >> student;
  }

  // Solve
  vector<size_t> lis(1, STUDENTS[0]);
  for (size_t it = 1; it < STUDENTS.size(); ++it)
  {
    if (STUDENTS[it] > lis[lis.size() - 1])
    {
      lis.push_back(STUDENTS[it]);
    }
    else
    {
      size_t lb = lower_bound(lis.begin(), lis.end(), STUDENTS[it]) - lis.begin();
      lis[lb] = STUDENTS[it];
    }
  }

  cout << N - lis.size() << '\n';

  return 0;
}
