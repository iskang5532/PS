// 1094 막대기
// https://www.acmicpc.net/problem/1094
/*
    비트마스킹 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 만들어야 하는 막대기의 길이 x는 잘게 나눈 막대기로 만들어야 하며, 잘게 나눈 막대기는 모두 2의 제곱수에 해당한다.
    2의 제곱수는 하나만 켜져 있는 비트로 나타낼 수 있음. 즉, x는 2의 제곱수를 얼마만큼 사용하냐가 됨.
    - x의 켜져 있는 비트의 개수를 파악해줌.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    int ans = 0;
    for (int i = 0; 1 << i <= 64; i++)
        if (n & 1 << i)
            ans++;

    cout << ans;
    // cout << __builtin_popcount(n);
}
