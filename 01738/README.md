**Problme No:** 01738
**Problem Id:** 골목길


Bellman-Ford로 풀면 무난하게 AC를 받는 문제이다.


단, 늘상 음수사이클 문제가 그러하듯이 사이클이 있을 때 뭘 출력할지를 잘 결정해주어여 한다.


이 문제 같은 경우는 **(1)**사이클이 있고, **(2)**사이클을 시작점에서 갈 수 있으며, **(3)**사이클에서 도착점에 갈 수 있을 때만 -1을 출력해야한다.
