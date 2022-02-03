**Problme No:** 17404
**Problem Id:** RGB 거리 2


덜 formal하지만, 보다 느낌오게 문제를 설명하면 아래와 같다.


- `1~N`번 집을 순서대로 원형으로 배치한 뒤, 색칠 할 때 이웃한 집끼리 다른 색으로 칠하는 최소 비용은?


DP로 풀어줄 수 있는데, 첫 집 / 끝 집 처리가 은근히 귀찮다.


우선, 첫 집 / 끝 집을 **무시하고**(즉, 일자로 늘어선 집들을 칠하는 것 처럼) 아래와 같이 CACHE를 정의하였다.


- `CACHE[i][first][last]`: `i`번 째 집까지, 첫 집의 색을 `first`로, 끝 집의 색을 `last`로 하여 색칠할 때 최소비용


첫 집, 끝 집 조건을 무시하므로 아래와 같이 아주 쉽게 점화식을 세워줄 수 있다.


- `CACHE[i+1][first][last] = min(CACHE[i][first][colour] + COST[i+1][last])`(단, colour != last)


이와 같이 풀어준 뒤, `min(CACHE[N][first][last])`(where first != last)를 구해주면 답을 구할 수 있다.
