**Problme No:** 09252
**Problem Id:** LCS 2


전형적인 DP문제이고, DP 완료 후 백트래킹 정도가 추가된 문제이다.


아래와 같이 CACHE를 정의하자.


- `CACHE[i][j]`: `A[0...i]`, `B[0...j]`까지 고려할 때 LCS의 길이


그럼 점화식은 아래와 같다.


- `CACHE[i][j] = max(CACHE[i-1][j-1] + 1, CACHE[i-1][j], CACHE[i][j-1])` (단, `CACHE[i-1][j-1] + 1` 항은 `A[i] == B[j]`일 때만 고려)
