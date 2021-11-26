/*
    11066 파일 합치기
    DP (2,880KB, 140ms)
    시간 복잡도: O(N^3) (3중 for문)
    문제: https://www.acmicpc.net/problem/11066
    풀이)
    - 이 문제의 특징은 서로 '인접'한 파일이 합쳐져야 한다는 것.
    - dp[i][j]일 경우, 구간 [i, j]까지의 최솟값을 저장.
    이를 구해주기 위해 각 구간의 값을 차근차근 구해줘야 하며, 구간의 범위(= l, r) 및 길이(= len)를 이용해야 한다.
    범위는 0부터 n-1까지이며, 길이는 1부터 n-1까지이다.. (실제로는 시작점에서부터 떨어진 거리이므로  일반적인 길이의 의미와는 다르다.)
    또한, 구해준 최솟값에 현재까지 구한 값을 추가로 더해줘야 하므로 구간에 포함된 값의 합(= 누적합)을 더해 저장해준다. (= 문제의 조건)
    - 구간에 포함된 값의 합을 이용해야 하며, 이를 쉽게 하도록 누적합을 만들어 값을 저장해준다. (또한 서로 인접한 구간만 연산할 수 있으므로 누적합 이용이 가능하다.)
    - 서로 인접한 값끼리 연산을 진행해야 하므로 dp를 구할 때 두 개의 구간인 왼쪽 구간과 오른쪽 구간으로만 나눠준다.
    - 범위를 len에 맞춰 탐색을 진행.
    1) 1인 경우
    - 구간을 나눌 방법은 하나이며, 이는 서로 인접한 값의 합이 가장 작은 값이 되므로 누적합을 이용해 값을 넣어줌.
    이후 l, r값을 변경해가며 나머지 범위를 탐색.
    2) 2인 경우
    - 구간을 나눠주며, [1][2]+[3], [1]+[2][3]의 결과중 가장 작은 값을 dp에 저장.
    이후 l ,r값을 변경해가며 나머지 범위를 탐색.
    3) ~n까지 2)를 반복해줌. 최종적으로 [0][n-1]이 모든 장을 합치는데 필요한 최소비용이 된다.
    etc.) 너무 어려웠음..
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

        int pSum[MAX]; // 누적합 (pSum[3] = 30일 때, 0~3까지의 합은 30)
        for (int i = 0; i < n; i++)
        {
            int k;
            cin >> k;
            pSum[i] = pSum[i - 1] + k;
        }
        int dp[MAX][MAX]; // dp[i][j]일 때, 구간 (i, j)에서의 최솟값
        for (int i = 0; i < MAX; i++)
            fill(dp[i], dp[i] + MAX, 0);

        for (int len = 1; len < n; len++) // 탐색 범위의 길이 (= 시작점에서부터의 거리; 1 == [1][2], 2 == [1][3], ...)
            for (int l = 0; l < n - len; l++) // 시작점 (len만큼의 범위를 탐색하므로 n-len으로 하여 범위를 초과하지 않게 해줌)
            {
                int r = l + len; // 끝점 (= 시작점에서부터 len만큼 떨어진 위치)

                dp[l][r] = INF; // 첫 비교 시 반드시 넣게 하기 위해 INF값을 넣어줌
                for (int mid = l; mid < r; mid++) // 구간을 나눠줄 중간값 (왼쪽 범위의 끝점 or 오른쪽 범위의 시작점-1)
                    dp[l][r] = min(dp[l][r],
                                   dp[l][mid] + dp[mid + 1][r] + pSum[r] - pSum[l - 1]); // 두 구간을 더해준 값에 누적합을 더해줌
            }

        cout << dp[0][n - 1] << endl;
    }
}