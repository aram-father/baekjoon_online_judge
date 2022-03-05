#include <cstdio>
#include <limits>
#include <algorithm>

using namespace std;

inline int abs(const int x)
{
	return x >= 0 ? x : -x;
}

const int kMaxN = 100000;

int N;
int LIQUID[kMaxN];

void Solve()
{
	int answer_thickness = numeric_limits<int>::max();
	int answer_lo;
	int answer_hi;

	int lo = 0;
	int hi = N - 1;
	while (lo < hi)
	{
		int sum = LIQUID[lo] + LIQUID[hi];
		if (abs(sum) < answer_thickness)
		{
			answer_thickness = abs(sum);
			answer_lo = lo;
			answer_hi = hi;
		}

		if (sum == 0)
		{
			break;
		}
		else if (sum < 0)
		{
			++lo;
		}
		else
		{
			--hi;
		}
	}

	printf("%d %d\n", LIQUID[answer_lo], LIQUID[answer_hi]);
}


int main(void)
{
	// Read Input
	scanf(" %d", &N);
	for (int it = 0; it < N; ++it)
	{
		scanf(" %d", &LIQUID[it]);
	}

	// Solve
	Solve();

	return 0;
}

