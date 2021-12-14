**Problme No:** 11054
**Problem Id:** 가장 긴 바이토닉 부분 수열


간단한 DP를 2번 돌려서 풀 수 있는 문제이다.


- `INCR[i]`: `NUMBER[i]`에서 끝나는 최장 부분 증가 수열


- `DECR[i]`: `NUMBER[i]`에서 시작하는 최장 부분 감소 수열


자명하게 답은 `max(INCR[i] + DECR[i] - 1)`이 된다.
