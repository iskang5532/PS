/* 
 * 11727 2xn 타일링 2
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/11727
 * ETC) 기존 2xn 타일링 문제에서 2x2 크기의 타일을 고려해야 하는 문제.
 * 2x2을 넣을 수 있는 [n == 2]부터 고려. 1x2 타일을 사용했을 때의 남는 공간이 n-2와 같았던 것처럼,
 * 2x2 타일을 사용했을 때의 남는 공간 또한 n-2와 같다. 그러므로, n-2를 두 번(*2) 이용하게 해준다.
 * 참고: 
 */

#include <iostream>

using namespace std;

#define endl "\n"
#define MOD 10007

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    int dp[1000] = {0};
    dp[0] = 0, dp[1] = 1, dp[2] = 3;

    for (int i = 3; i <= n; i++)
        dp[i] = (dp[i - 1] + (dp[i - 2] * 2)) % MOD;

    cout << dp[n];
}