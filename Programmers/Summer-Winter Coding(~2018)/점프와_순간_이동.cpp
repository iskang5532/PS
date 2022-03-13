/*
    점프와 순간 이동 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 점프와 순간 이동)
    시간 복잡도: ?
    문제:
    etc.) 패턴을 알아내는데 시간이 오래 걸림. 추가로, 비트를 이용하여 푼 분들이 계시는 데 정말 신기했음.
    - 예제를 보면 특정한 값에 1을 더해 나온 값으로 n을 구함.
    - 특정한 값을 구하기 위해서는 엄청난 경우의 수를 이용해야 하는데, 그렇게 할 경우 시간 초과. (if n == 10^9)
    때문에 앞에서부터 값을 특정하여 구하는 것이 아닌, 구해야할 값 n을 특정한 값으로 봄. (top-down?)
    - 점프는 순간이동 시 기준점에서부터 x2이므로, n을 이용하였을 떄는 ÷2를 해줌.
    만약 ÷2를 했을 때 나머지가 남아버리는 홀수인 경우, 순간이동이 아닌 점프를 해야 하는 순간이므로 한 칸 점프해주며 값을 저장해준다.
 */

#include <string>
#include <vector>

using namespace std;

int solution(int n)
{
    int ans = 1; // n == 1인 경우를 포함
    while (n != 1)
    {
        if (n & 1) // 홀수인 경우, 짝수로 만들어줌
            n--, ans++;
        n >>= 1;
    }

    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution(5) << endl;
//     cout << solution(6) << endl;
//     cout << solution(5000) << endl;
// }