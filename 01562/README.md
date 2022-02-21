**Problme No:** 01562
**Problem Id:** 계단수


결론부터 기술하면, 각 숫자의 사용여부를 비트마스킹을 활용하여 나타내는 DP 문제이다.


비트마스킹을 써야한다는 것도, CACHE 정의까지도 스스로 생각이 닿았는데 점화식을 스스로 세우지 못했다.


문제를 Bottom-up DP로 풀 때, 각 루프 바디에서 어떤 값을 구할 건지를 제대로 설계하지 못한 탓인듯 하다.


각설하면, 아래와 같이 CACHE를 정의한다.


- `CACHE[n][d][mask]`: `n`자리 수 중 마지막 수가 `d`이고, 숫자 사용여부가 `mask`와 같은 계단 수의 갯수


위의 CACHE를 가지고 점화식을 세우려고 노력하다보니 `mask`를 고정해놓고, 이전 상태들을 활용하여 하였는데 이것이 패착이었다.


실제 루프는 아래와 같이도는데, 교훈은 아래와 같다.


- 루프를 이전 상태의 `mask` 기준으로 돌리고, `d`를 여기에 masking하여 구하고자 하는 현재 상태를 찾아준다.

아 참, 내 실수만 설명하다보니 점화식의 아이디어를 기술하는 것을 잊었다.

점회식의 아이디어는 `n-1`자리 수에다가 `d`를 덧붙여 `n`자리의 계단 수를 만드는 것이다.


```c++
// Solve
for (int num_of_digits = 2; num_of_digits <= N; ++num_of_digits)
{
    for (int ending_digit = 0; ending_digit < 10; ++ending_digit)
    {
        for (int prev_used = 0; prev_used < (1 << 10); ++prev_used)
        {
            int next_used = prev_used | (1 << ending_digit);

            if (ending_digit != 0)
            {
            CACHE[num_of_digits][ending_digit][next_used] += CACHE[num_of_digits - 1][ending_digit - 1][prev_used];
            CACHE[num_of_digits][ending_digit][next_used] %= kMod;
            }

            if (ending_digit != 9)
            {
            CACHE[num_of_digits][ending_digit][next_used] += CACHE[num_of_digits - 1][ending_digit + 1][prev_used];
            CACHE[num_of_digits][ending_digit][next_used] %= kMod;
            }
        }
    }
}

```
