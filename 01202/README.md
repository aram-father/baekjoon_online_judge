**Problme No:** 01202
**Problem Id:** 보석 도둑


DP로 풀어야 한다는 강박에서만 벗어나오면 금방 풀 수 있다.


작은 가방부터 채워나간다고 생각해보자.


지금 보고 있는 가방에 들어갈 수 있는 보석들의 후보를 찾은 뒤 이 중 가장 비싼 보석을 채워주면 된다.


어차피 다음에 볼 가방에는 지금 후보들이 다 들어갈 수 있으므로 greedy property도 만족이 되리라.


이때, 아래와 같은 문제점이 떠올랐었다.


- "아니?!, 보석들 중 (1)현재 보고 있는 가방의 무게 제한 범위 내에서, (2)가장 비싼 녀석을 찾아야 되네"
- "뭔가 세그먼트 트리를 쓰는 라인 스위핑과 비슷하다!"


이런 유형의 문제는 보통 두 개의 기준으로 쿼리/정렬을 잘하려고 애쓰는 것 보다, 한개의 기준은 스위핑 순서를 통해 맞춰주면 된다.


설명이 지나치게 철학적인데, 결국 아래와 같이 풀었다는 이야기이다.


- 가방을 무게 제한 기준으로 오름차순 정렬한다.
- 보석을 무게 제한 기준으로 오름차순 정렬한다.
- 가방을 앞에서부터 순서대로 보면서
  - 현재 가방에 들어갈 수 있는 보석들을 priority queue에 집어 넣는다(정렬은 가격 기준으로)
  - 다 집어넣은 후에 top에 있는 보석을 현재 보고 있는 가방에 넣어주면 된다.


보석을 무게 제한 기준으로 정렬한 뒤에 스위핑한 것이 한 개 기준을 스위핑 순서를 통해 맞춰준 것으로 이해하면 된다.