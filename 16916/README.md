**Problme No:** 16916
**Problem Id:** 부분 문자열


아주 straight-forward하게 KMP를 묻는 문제인데, 역시나 난관은 KMP를 잘 기억하고 있냐는 것이다.


연습이 왕도겠지만, 팁을 적어놓자면 아래와 같다.


- 일단 table이 있다고 가정하고 haystack/needle을 찾는 코드를 짠다.
- table을 구하는 방법은 needle에서 needle을 찾는 코드라는 점을 기억하자.
