**Problme No:** 10942
**Problem Id:** 팰린드롬?


문제 설명이 조금 부족한데, 숫자 하나를 문자 하나로 취급해야 한다.


여튼 노말하게 DP를 써주면 풀리는 문제이다.


아래와 같이 CACHE를 정의하자.


- `CACHE[s][e]` = s ... e 번째 수가 palindrome인가?

점화식은 아래와 같다.


- `CACHE[s][e] = (CACHE[s+1][e-1] && N[s] == N[e]) ? 1 : 0`
