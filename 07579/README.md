**Problme No:** 07579
**Problem Id:** 앱


딱 보면 Kanpsack 문제임을 알 수 있다.


순간 전형적인 0-1 Knapsack이 아닌가 생각했었는데, 입력을 보니 `메모리 = 무게, 횔성화 시간 = 비용`으로 정의해서 최소 비용 DP를 수행하기에는 입력이 너무 크다.


골드 수준의 문제이기 때문에, 별 다른 의심 없이 적당히 CACHE 정의를 바꾸어주면 되겠거니 생각했고, 그생각이 맞았다. ㅎㅎ...


아래와 같이 CACHE를 정의하자.


- `CACHE[idx][act]`: `idx`번째 앱까지 고려할 때 총 활성화 시간 `act`로 만들어낼 수 있는 최대의 메모리 양


그럼 아래와 같이 점화식을 세워줄 수 있다.


- `CACHE[idx][act] = max(CACHE[idx-1][act], CACHE[idx-1][act-ACTIVATE[idx]])`


DP를 통해 모든 부분문제를 풀어준 뒤, `CACHE[N-1][x] >= M`이 되는 최소의 `x`를 찾아주면 답을 구할 수 있다.


별로 어려울 것 없는 문제인데, 또 나쁘지도 않은 문제이니 아래 내용 정도를 기억해두자.


- knapsack인 것 같은데 문제 공간이 너무 크다면 cache 정의 변경을 생각해보자
- knapsack인 것 같은데 이상/이하 같은 표현이 나온다면 cache 정의 변경을 생각해보자
