**Problme No:** 05419
**Problem Id:** 북서풍


segment tree를 활용한 sweeping으로 쉽게 풀 수 있다.


물론 좌표 압축은 해주어야 한다.


- 압축된 y축을 index로하는 segment tree를 x축을 훑으면서 구축해나간다.
- 이번에 보는 정점보다 y좌표가 북쪽에 위치하는 정점들의 수를 segment tree를 통해 구한다.
(sweeping을 x축을 따라 진행하므로 이미 segment tree에 있는 정점들은 모두 이번에 보는 정점보다 서쪽에 있음이 보장됨)
- 이번에 본 정점도 segment tree에 업데이트 해준다.


굳이 한가지 까다로운 점을 꼽자면, 정북/정서쪽에 있는 정점도 고려해줘야 한다는 점인데, 이는 위의 알고리즘을 그대로 사용하되 정점을 x좌표 **오름차순**, y좌표 **내림차순**으로 정렬한 뒤 스위핑을 수행하면 된다.

