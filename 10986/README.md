**Problme No:** 10986
**Problem Id:** 나머지 합


초반에 DP 문제겠거니 생각해보다가 DP 문제가 아님을 깨닫는데까지 시간이 조금 걸렸다.


결과적으로 문제는 스위핑의 아이디어를 활용해서 풀었다.


주어진 입력을 통해 풀이를 살펴보면 아래와 같다.


`1 2 3 1 2` 입력에 대해 아래와 같이 PSUM을 함께 구해서 테이블로 표현해보자.


| index | 0 | 1 | 2 | 3 | 4 | 5 |
|-|-|-|-|-|-|-|
| number | | 1 | 2 | 3 | 1 | 2 |
| psum | 0 | 1 | 3 | 6 | 7 | 9 |


이제 `index i`로 끝나는 연속부분 수열 중 합이 법 M에 대해 0이 되는 경우를 헤아려야 한다고 생각해보자.


자명하게 이런 경우의 수는 `PSUM[i] == PSUM[j] mod M (단, j < i)`을 만족하는 `j`의 수와 같음을 알 수 있다.

(`PSUM[i] - PSUM[j]`가 곧 `index j+1` ~ `index i`까지의 합이므로)


따라서, 구한 `PSUM` 배열을 앞에서부터 스위핑해주면서 위의 조건을 만족하는 경우의 수를 누적하여 더해주면 된다.


이 때, 현재까지 스위핑한(본) `PSUM`중 나머지가 `k`였던 원소의 수를 `MOD[k]` 배열에 갱신해줌으로써 쉽게 경우의 수를 헤아려 줄 수 있다.


이는 x-y 평면등을 스위핑하는 문제에서 y를 구간으로 풀 때, x를 스위핑하는 순서를 통해 맞춰주는 것과 유사함을 기억하자.
