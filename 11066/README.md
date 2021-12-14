**Problme No:** 11066
**Problem Id:** 파일 합치기


매우 간단한 DP 문제이나, 테스트케이스 수가 주어지지 않아 "이게 정말 TLE 안나고 풀릴까?"를 고민하게 만드는 문제이다.


간단한 DP로 풀어주면 TLE 안나고 정답이 나온다.


CACHE 정의는 아래와 같이 한다.


- `CACHE[i][j]`: 파일 `i ~ j`를 합칠 때 최소 비용


점화식은 아래와 같다.


- `CACHE[i][j]` = `CACHE[i][m]` + `CACHE[m+1][j]` + `PSUM[j] - PSUM[i] + FILE[i]` (i < j)
- `CACHE[i][j]` = 0 (i >= j)
