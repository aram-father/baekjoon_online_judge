**Problme No:** 12844
**Problem Id:** XOR


별 탈 없이 lazy propagation을 사용하는 segment tree를 사용해서 풀 수 있는 문제다.


개인적으로는 화성탐사가 훨씬 어려운데 왜 똑같이 플레3인지 모르겠다.


어찌되었건...구간합을 구하는 lazt propagation과 다른 점은 xor을 사용하므로서 아래의 2가지 문제가 생긴다는 점이다.


1. 쿼리 구간과 노드 구간이 겹치지 않을 때 뭘 반환해주나?
- 구간 합에서는 덧셈의 항등원인 0을 반환해주었었다.
- 이 문제에서는 xor의 항등원인 0을 반환해주면 된다.


2. lazy를 적용시킬 때 노드 구간 길이 만큼 lazy를 xor하는 작업을 어떻게 해주면 되나?
- 구간 합에서는 단순하게 `구간길이 x lazy`를 해주었었다.
- 이 문제에서는 구간길이가 홀수이면 lazy를 1번 xor, 짝수이면 안해주면 된다(xor의 성질을 생각하면 자명하다)
