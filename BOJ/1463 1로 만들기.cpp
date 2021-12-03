/*
    1463 1로 만들기
    DP (5,804KB, 8ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/9095
    풀이)
    - dp[i] = k일 때, 값 i에서 1로 만들 때 최소 연산 횟수는 k. ex) dp[10] = 3은 '10'을 1로 만들 때의 최소 횟수는 '3')
    - 3으로 나누기와 2로 나누기, 그리고 1을 빼는 세 가지의 연산이 있다.
    그러므로 값 i로 세 연산을 수행했을 때, 가장 작은 결과가 나오는 연산을 수행시킨다.
    단, 11과 같이 3 혹은 2로 나눠떨어지지 않는 값은 제외한다.. (= if문)
    - 각 연산에 +1이 붙는데, 이는 현재 수행하는 연산의 횟수이다. (이전 값에서 현재 값으로 오려면 연산을 한번 수행해야 하는 것과 같음)
    etc.) 어렵다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 987654321
#define MAX 1'000'000 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n;
    cin >> n;

    int dp[MAX];
    fill(dp, dp + MAX, INF);
    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 1;
    for (int i = 4; i <= n; i++)
    {
        if (i % 3 == 0) // ÷3
            dp[i] = min(dp[i], dp[i / 3] + 1);
        if (i % 2 == 0) // ÷2
            dp[i] = min(dp[i], dp[i / 2] + 1);
        dp[i] = min(dp[i], dp[i - 1] + 1); // -1
    }

    cout << dp[n];
}