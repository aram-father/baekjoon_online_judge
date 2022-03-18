#include <set>
#include <cstdio>

using namespace std;

int G;
int P;
int PLANES[100000];

int main(void)
{
  scanf(" %d", &G);
  set<int> gates;
  for (int g = 1; g <= G; ++g)
  {
    gates.insert(-g);
  }

  scanf(" %d", &P);
  for (int it = 0; it < P; ++it)
  {
    scanf(" %d", &PLANES[it]);
  }

  int answer;
  for (answer = 0; answer < P; ++answer)
  {
    auto it = gates.lower_bound(-PLANES[answer]);
    if (it == gates.end())
    {
      break;
    }
    else
    {
      gates.erase(it);
    }
  }

  printf("%d\n", answer);

  return 0;
}
