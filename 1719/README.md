**Problme No:** 1719
**Problem Id:** 택배

1. 일단 플로이드-워셜을 수행한다.


2. DIST[src][dst] == W(src, x) + DIST[x][dst]가 만족한다면, src에서 dst로 이동할 때 가장 먼저 x부터 방문해야 한다는 이야기이다.
