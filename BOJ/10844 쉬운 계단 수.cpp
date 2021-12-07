/*
    10844 쉬운 계단 수
    DP (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/10844
    풀이)
    - 문제를 풀 때 주의할 점은, 0과 9는 서로 계단 수가 아니라는 점. 또한, 출력에서 dp값들을 더해주는 과정에서 MOD를 넘을 수 있음.
    - dp[i][j] = k라고 할 때, 길이 i의 j로 끝나는 수를 만들 수 있는 계단 수의 개수는 k개.
    - j를 수의 시작점이 아닌 끝점으로 맞춘 이유는, 0이 앞으로 올 수 없으며 이를 고려할 경우 복잡해지기 때문
 */

#include <iostream>
#include <numeric> // accumulate

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 100 + 1
#define MUL 1'000'000'000

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n;
    cin >> n;

    int dp[MAX][10];
    for (int i = 0; i <= n; i++)
        fill(dp[i], dp[i] + 10, 0);

    for (int i = 1; i <= 9; i++)
        dp[1][i] = 1;

    for (int len = 2; len <= n; len++) // 자릿수
    {
        dp[len][0] = dp[len - 1][1]; // 0으로 끝나는 수의 계단 수는 1
        for (int i = 1; i <= 8; i++) // i로 끝나는 수의 계단 수를 구해줌.
            dp[len][i] = (dp[len - 1][i + 1] + dp[len - 1][i - 1]) % MUL;
        dp[len][9] = dp[len - 1][8]; // 9로 끝나는 수의 계단 수는 9
    }

    cout << accumulate(dp[n], dp[n] + 10, 0LL) % MUL;
}