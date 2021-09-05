/* 
 * 1958 LCS 3
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1958
 * etc.) 세 문자열의 LCS를 구하는 문제.
 * 기존 두 문자열에서 LCS를 구할 때는 2차원 배열을 이용하였지만, 문자열이 추가되었기 때문에 3차원 배열을 이용.
 */

#include <iostream>
#include <algorithm> // std::max

using namespace std;

#define endl "\n"
#define MAX 100 + 1

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    string p, q, r;
    cin >> p >> q >> r;

    int dp[MAX][MAX][MAX] = {0};
    for (int i = 1; i <= p.length(); i++) // dp[0] == 0을 유지시키기 위해 1부터
        for (int j = 1; j <= q.length(); j++)
            for (int k = 1; k <= r.length(); k++)
                if (p[i - 1] == q[j - 1] && q[j - 1] == r[k - 1]) // 문자가 같은 경우 (문자열의 시작점은 0부터이기 때문에 -1)
                    dp[i][j][k] = dp[i - 1][j - 1][k - 1] + 1;    // 대각선 값 + 1
                else
                    dp[i][j][k] = max({dp[i - 1][j][k], dp[i][j - 1][k], dp[i][j][k - 1]}); // 이전 값들 중 큰 값을 가짐

    cout << dp[p.length()][q.length()][r.length()];
}