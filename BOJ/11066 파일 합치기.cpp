/*
    11066 파일 합치기
    DP (2,880KB, 140ms)
    시간 복잡도: O(N^3) (3중 for문에서의 시간 복잡도)
    문제: https://www.acmicpc.net/problem/11066
    etc.) 너무 어려웠음..
    - 이 문제의 특징은 서로 인접한 파일이 합쳐져야 한다는 것.
    - 누석합을 이용하기 때문에 배열을 [1]부터 사용.
    참고: https://cocoon1787.tistory.com/317 (이론)
 */

#include <iostream>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 1234567890
#define MAX 500 + 1

int pSum[MAX];
int dp[MAX][MAX]; // dp[i][j]일 때, 구간 (i, j)에서의 최솟값

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;
    while (tc--)
    {
        int n; // 장의 수 (3 ≤ n ≤ 500)
        cin >> n;
        for (int i = 1; i <= n; i++)
        {
            int k;
            cin >> k;
            pSum[i] = pSum[i - 1] + k;
        }

        for (int gap = 1; gap < n; gap++)
            for (int l = 1; l <= n - gap; l++)
            {
                int r = l + gap;
                dp[l][r] = INF; // 첫 값을 위해 최대치로
                for (int mid = l; mid < r; mid++)
                    dp[l][r] = min(dp[l][r],
                                   dp[l][mid] + dp[mid + 1][r] + pSum[r] - pSum[l - 1]); // 두 구간을 더해준 값에 누적합을 더해줌
            }

        cout << dp[1][n] << endl;
    }
}