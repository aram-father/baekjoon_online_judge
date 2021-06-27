**Problme No:** 11408
**Problem Id:** 열혈강호 5


전형적인 min-cost-max-flow 문제이다.


1. `source`에서 `employee_i`로 간선을 연결하는데, (`source`, `employee_i`)의
  - capacity는 1
  - cost는 0


2. `work_j`에서 `sink`로 간선을 연결하는데, (`work_j`, `sink`)의
  - capacity는 1
  - cost는 0


3. `employee_i`에서 `work_j`로 간선을 연결하는데, 이때 (`employee_i`, `person_j`)의
  - capacity는 무한
  - cost는 월급으로 한다.


4. max flow와 min cost가 답이 된다.

