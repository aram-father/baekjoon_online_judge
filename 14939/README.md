**Problme No:** 14939
**Problem Id:** 불 끄기


행 단위로 각 행에 있는 전구를 누를지 말지 결정한다고 해보자.


`i`번쨰 행의 `j`번째 열에 위치하는 전구를 고려할 때, 사실 얘를 누를지 말지는 `i-1`행 `j`열의 전구가 결정한다.


문제의 특성상 만약 윗 행의 전구가 켜져 있다면 누르지 않고서는 얘를 꺼줄 방법이 없기 때문이다.


따라서, 첫 행만 전 탐색해주고 나머지 행은 그리디로 진행해주면 된다.