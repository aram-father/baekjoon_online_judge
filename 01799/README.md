**Problme No:** 01799
**Problem Id:** 비숍


별 볼일 없는 Backtracking 문제지만, 무식하게 풀면 TLE가 나고, 주의 깊지 못하면 WA가 날 수 있다.


시간복잡도는 아래 테크닉으로 줄인다.


- 대각 체크 배열 활용하기
- 흰 칸, 검은 칸 나눠 풀기(서로 영향 안미치므로 가능하고, 이게 복잡도를 크게 줄인다)


주의할 점으로는 체스판 사이즈가 홀수냐 짝수냐에 따라서 다음 인덱스 계산이 달라진다는 점이 있다.