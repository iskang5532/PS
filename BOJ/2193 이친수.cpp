/*
    2193 이친수
    DP (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2193
    풀이)
    - 1에서부터 6까지의 n에 대한 정답을 구했을 시, dp[i] = dp[i-1] + dp[i-2]와 같은 점화식을 얻을 수 있음. (= 피보나치 수열)
    - 추가로, 47의 값부터 29억이 넘어가며, 이는 int의 범위에서 벗어남. 그러므로 long long을 사용하여 오버플로우를 막아줌.
    etc.) 낮은 수에 대한 결괏값을 구하여 피보나치 수열인지를 파악하는 것이 관건이라고 생각.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 90 + 1
typedef long long ll;

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 1 ≤ n ≤ 90
    cin >> n;

    ll dp[MAX]; // i번째 피보나치 수를 저장
    fill(dp, dp + MAX, 0);

    dp[1] = dp[2] = 1;
    for (int i = 3; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];

    cout << dp[n];
}

// n  dp[n]
// 1   1    1
// 2   1    10
// 3   2    101 100
// 4   3    1000 1001 1010
// 5   5    10000   10001   10010   10100   10101
// 6   8    100000  100001  100010  100100  100101  101000  101001 101010