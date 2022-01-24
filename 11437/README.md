**Problme No:** 11437
**Problem Id:** LCA


입력의 크기가 매우 작아서 단순한 알고리즘으로도 풀린다.


우선, 입력에 별도로 부모 자식 관계가 주어지지는 않으므로 입력을 그래프로 간주하여 받은 뒤 루트를 1번 노드로하는 BFS 트리를 생성해준다.


이 때 각 노드의 깊이를 함께 구해주도록 하자.


만약, a와 b의 LCA를 찾고자한다면, 아래의 방법을 따르면 된다.


- Case 1) a와 b의 깊이가 같다면, a와 b를 1칸 씩 부모로 옮겨가면서 만날 때까지 옮겨준다.
- Case 2) a와 b의 깊이가 다르다면(편의상 a가 더 깊다고하자), a를 b의 깊이까지 올려준 뒤에 Case 1)을 적용한다.


입력의 크기가 작아서 Case 2)에서 타고올라가는 부분을 간단하게 작성했는데, 입력이 큰 문제의 경우 아래와 같이 DP 아이디어를 함께 적용해서 풀어주어야 한다.


- `PARENT[i][k]`: `i`번 노드의 `2^k`번째 부모
- `PARENT[i][k]` = `PARENT[PARENT[i][k-1]][k-1]`