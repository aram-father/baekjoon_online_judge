**Problme No:** 11049
**Problem Id:** 행렬 곱셈 순서


그닥 어려울 것 없는 DP 문제로 쉽게 쉽게 풀어줄 수 있다.


아래와 같이 CACHE를 정의하자.


- `CACHE[s][e]`: `Matrix[s]`부터 `Matrix[e]`까지 곱할 때 최소의 연산횟수


그럼 점화식은 아래와 같이 유도할 수 있다.


- `CACHE[s][e] = min(CACHE[s][m] + CACHE[m+1][e] + Matrix[s].row * Matrix[s].col * Matrix[e].col)`


결국 `Matrix[s..e]`를 `m`을 기준으로 두 파트로 나누어 보며 접근한다는 이야기이다.


굳이 주의할 점을 꼽아보자면 Bottom-up DP로 풀려면 루프 순서를 주의해주어야 한다는 점 정도가 있다.
