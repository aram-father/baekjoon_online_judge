**Problme No:** 01328
**Problem Id:** 고층빌딩


DP 솔루션의 점화식을 발견하기 직전까지 갔지만, 근처에서 배회하다가 결국에는 답을 보고 풀었다.


캐시는 아래와 같이 정의한다.


`CACHE[bldg][left][right]`: `[bldg, N]` 높이를 갖는 빌딩들을 왼편에서 `left`개가 보이고 오른편에서 `right`개가 보이도록 배치하는 경우의 수


점화식은 아래와 같이 구할 수 있다.


`CACHE[bldg][left][right]` = `CACHE[bldg + 1][left - 1][right]` + `CACHE[bldg + 1][left][right - 1]` + `CACHE[bldg + 1][left][right] * (N - bldg - 1)`


각 항의 의미를 하나씩 살펴보도록 하자.


- `CACHE[bldg + 1][left - 1][right]`: `[bldg + 1, N]` 높이를 갖는 빌딩들을 왼편에서 `left - 1`개가 보이고 오른편에서 `right`개가 보이도록 배치하는 경우의 수이다. 단순히 제일 왼편에 `bldg` 높이를 갖는 빌딩을 가져다 놓아주면 `CACHE[bldg][left][right]`의 경우 중 하나가 될 수 있다.
- `CACHE[bldg + 1][left][right - 1]`: `CACHE[bldg + 1][left - 1][right]` 경우와 유사하나 제일 오른편에 빌딩을 가져다 놓아주는 경우이다.
- `CACHE[bldg + 1][left][right] * (N - bldg - 1)`: `bldg` 높이를 갖는 빌딩이 최우/좌측에 위치하지 않는다면, 이미 놓여져 있는 빌딩 사이사이 어디든 아무데나 넣어주어도 죄/우측에서 바라보는 빌딩 수가 변하지 않는다. 왜냐하면 `CACHE[bldg + 1][left][right]`의 경우가 세어주는 빌딩의 높이는 모두 `bldg`보다 높으니까.


구현할 때는 `bldg` 번호를 큰 놈부터 붙였다.

