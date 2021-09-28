**Problme No:** 01561
**Problem Id:** 놀이 공원


예제 3번에 대해서 M개 놀이기구가 사람을 태울 수 있는 시간을 테이블로 표현해보자.


- 1번 놀이기구: 0 1  2  3  4  5 ...
- 2번 놀이기구: 0 2  4  6  8 10 ...
- 3번 놀이기구: 0 3  6  9 12 15 ...
- 4번 놀이기구: 0 4  8 12 16 20 ...
- 5번 놀이기구: 0 5 10 15 20 25 ...


이제 위에 주어진 테이블의 모든 숫자를 오름차순으로 정렬해보자.


단, 이 때 같은 숫자에 대해서는 더 작은 놀이기구 번호의 숫자가 앞에 오게 정렬하자.


- 0, 0, 0, 0, 0, 1, 2, 2, 3, 3, 4, 4 ...


위와 같이 하면 결국에 N번째에 오는 숫자의 놀이기구가 곧 N번 학생이 이용하게 될 놀이기구의 갯수가 된다.


여기까지 보면 굉장히 간단한데, 문제를 잘보면 정렬할 숫자들의 갯수의 하한으로 볼 수 있는 N의 범위가 너무 크다.


따라서, 방금 위에서 언급한 아이디어를 정렬 **없이** 바이너리 서치를 통해 구현해보도록 하자.


- `X분까지 서비스한 횟수`(놀이기구를 태워준 학생의 수)가 N 이상이 되는 가장 빠른 `X분`을 찾아주면 `X분`에 사람을 태운 놀이 기구 중에 하나가 곧 N번 학생이 타게될 놀이 기구이다.
(`X분`에 사람을 태운 놀이 기구는 여러개 일 수 있음에 주의하자)
- 즉, `[0, 2000000000*30 + 1)`에서 서비스 횟수의 **lower_bound N** 을 찾으면 된다.
- binary search 과정에서 임의의 `Middle`에 대하여 `Middle분까지 서비스한 횟수`는 아래 각 놀이 기구 서비스 횟수의 합이며, 아래와 같이 구할 수 있다.
  - Middle분 이하의 1번 놀이기구 서비스 횟수(0분을 포함한 Middle이하 1의 배수의 갯수)
  - Middle분 이하의 2번 놀이기구 서비스 횟수(0분을 포함한 Middle이하 2의 배수의 갯수)
  - Middle분 이하의 3번 놀이기구 서비스 횟수(0분을 포함한 Middle이하 3의 배수의 갯수)
  - Middle분 이하의 4번 놀이기구 서비스 횟수(0분을 포함한 Middle이하 4의 배수의 갯수)
  - Middle분 이하의 5번 놀이기구 서비스 횟수(0분을 포함한 Middle이하 5의 배수의 갯수)
- 위 과정을 통해 알아낼 수 있는 사실은 N번 학생이 몇 분에 놀이 기구를 타냐는 것이다(편의상 `X분`이라하자)
- 이제 `X-1분` 까지의 서비스 횟수를 다시 구하고, `X분`에 학생을 태우는 과정을 시뮬레이션해주면서 N번 학생의 차례를 찾아주면 된다.