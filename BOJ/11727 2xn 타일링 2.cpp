/* 
 * 11727 2xn Ÿ�ϸ� 2
 * DP
 * �ð� ���⵵: ?
 * ����: https://www.acmicpc.net/problem/11727
 * ETC) ���� 2xn Ÿ�ϸ� �������� 2x2 ũ���� Ÿ���� ����ؾ� �ϴ� ����.
 * 2x2�� ���� �� �ִ� [n == 2]���� ���. 1x2 Ÿ���� ������� ���� ���� ������ n-2�� ���Ҵ� ��ó��,
 * 2x2 Ÿ���� ������� ���� ���� ���� ���� n-2�� ����. �׷��Ƿ�, n-2�� �� ��(*2) �̿��ϰ� ���ش�.
 * ����: 
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