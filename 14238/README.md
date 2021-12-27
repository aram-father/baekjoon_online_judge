**Problme No:** 14238
**Problem Id:** 출근 기록

문제를 보고 2-30분 가량 감을 못 잡아서 문제 분류를 보았다.

문제 분류는 다이나믹 프로그래밍으로 되어 있는데, 더욱이 감을 잡기가 어려워서...결국엔 답을 보았다.

결론적으로는 재귀를 활용하는 Top-down DP 문제였는데, 골3인데도 헤매인 것 보면 이 부분에 대한 복습이 필요한 상태인 것 같다.



우선, 아래와 같이 `CACHE`를 정의한다.

- `CACHE[na][nb][nc][prev_prev][prev]`: 바로 전날 `prev`가 출근하였고, 전전날 `prev_prev`가 출근하였을 때, A, B, C를 각각 `na`, `nb`, `nc`번 출근하게 하는 출근 기록 작성이 가능한가?(**boolean**)



점화식(이라는 표현보다는 코드지만)은 아래와 같이 세워 줄 수 있다.

```c++
if (na ==  0 && nb == 0 && nc == 0) // 더 이상 출근시킬 인원이 없음
{
    CACHE[na][nb][nc][prev_prev][prev] = true;
}
else if (na > 0 && CACHE[na - 1][nb][nc][prev][A]) // A를 출근 시킬 수 있음
{
    CACHE[na][nb][nc][prev_prev][prev] = true;
}
else if (nb > 0 && && prev != B && CACHE[na][nb - 1][nc][prev][B]) // B를 출근 시킬 수 있음
{
    CACHE[na][nb][nc][prev_prev][prev] = true;
}
else if (nc > 0 && prev != C && prev_prev != C && CACHE[na][nb][nc - 1][prev][C]) // C를 출근 시킬 수 있음
{
    CACHE[na][nb][nc][prev_prev][prev] = true;
}
else // 불가능
{
    CACHE[na][nb][nc][prev_prev][prev] = false;
}
```



위의 점화식으로 DP를 돌려주고, 가능한 경우 백트래킹을 통해 아무 해나 하나를 구해주면 된다.

참고로, A는 전일/전전일 출근자에 대한 아무 제약이 없는 인원이므로 `Solve(NA, NB, NC, **A**, **A**)`와 같이 초기 호출의 `prev`, `prev_prev`를 A로 가정해주었다.

