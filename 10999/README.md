**Problme No:** 10999
**Problem Id:** 구간 합 구하기 2


lazy propagation을 사용하는 segment tree 문제이다.


사실 알고리즘이 어렵다기 보다는 구현하다가 재귀의 늪에 빠지는 경우가 더 많다.


또 헤매이는 경우를 방지하기 위해 몇 가지 메모를 남긴다면,


1. 생각보다 훨씬 더 게으르게 하자
  - update할 때는 propagation을 하지 않는다.
  - propagation할 때는 내 자식 노드까지만 진행해준다(어차피 이후 Query의 재귀를 타고 내려가면서 propagation된다).


2. update는 유효한 구간이건 아니건 자신이 담당하는 구간([root_left, root_right])의 합을 출력해주어야 한다.
  - 생각하면 당연한데, 이걸 간과해서 WA를 2번 받았다.

