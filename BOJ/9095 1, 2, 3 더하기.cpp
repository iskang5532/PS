/*
    9095 1, 2, 3 더하기
    DP (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/9095
    풀이)
    - DP[i] = k일 때, 값 i를 만들 수 있는 경우의 수는 k.
    - 1, 2, 3, 4의 결과는 각각 1, 2, 4, 7이다.
    이를 봤을 때, i번째의 값은 이전의 세 값을 더하면 얻을 수 있다는 걸 알 수 있다.
    etc.) 거의 하루종일 고민한 문제. 보일듯 하면서 안보였던 점화식..
    - DP문제는 작은 값들에 대한 정답을 나열시킨 뒤, 보면서 곰곰이 생각하는 편이 좋은듯.
    - 정답을 알고난 후면 "아하" 싶은데, 모를 때는 진짜 잘 안보이는게 DP인듯.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 11 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;

    int dp[MAX];
    dp[0] = dp[1] = 1;
    for (int i = 2; i < MAX; i++)
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];

    while (tc--)
    {
        int n; // 1 ≤ n ≤ 11
        cin >> n;
        cout << dp[n] << endl;
    }
}