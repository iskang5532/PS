/*
    2576 계단 오르기
    DP (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2576
    풀이)
    - dp[i] = k일 때, i번쨰 계단을 밟을 때의 최댓값은 k.
    - i번째 계단에 도달할 수 있는 두 가지 경우 중 최댓값을 dp에 저장.
     - 첫 번째 경우: i-1번째 계단을 밟아서 i번째에 도착.
     이 경우, i-2번째 계단을 밞으면 안되므로 i-3번째 계단에서 i-1로 와야 한다. 그러므로 i-3번째의 dp값을 이용해줌.
     - 두 번째 경우: i-2번째 계단을 밟아서 i번째에 도착.
     이 경우, i-2번째에서 곧바로 i번째로 이동했으므로 i-2번째의 dp값을 이용.
    점화식: dp[i] = 현재 계단 + max(i-1 계단 + i-3 최댓값, i-2번째 최댓값)
    etc.) 엄청 어려운 정도는 아녔음. (적당히..)
    - dp 선언 시에 초깃값([0], [1], ..)을 설정해주면 점화식을 세울 때 도움이 되는듯.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 300 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n;
    cin >> n;
    int stair[MAX];
    for (int i = 0; i < n; i++)
        cin >> stair[i];

    int dp[MAX];

    dp[0] = stair[0];
    dp[1] = stair[0] + stair[1];
    // dp[2] = stair[2] + max(stair[1], stair[0]);
    for (int i = 2; i < n; i++)
        dp[i] = stair[i] + max(stair[i - 1] + dp[i - 3], dp[i - 2]);

    cout << dp[n - 1];
}