/*
    2262 토너먼트 만들기
    DP (2,416KB, 4ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2262
    풀이)
    - 이 문제의 특징은 서로 '인접'한 파일이 합쳐져야 한다는 것.
    - dp[i][j]일 경우, 구간 [i, j]까지의 최솟값을 저장.
    이를 구하기 위해 각 구간의 값을 차근차근 구해줘야 하며, 구간의 범위(= l, r) 및 길이(len)를 이용해야 한다.
    범위는 0부터 n-1까지이며, 길이는 1부터 n-1까지이다. (실제로는 시작점에서부터 떨어진 거리이므로 일반적인 길이의 의미와는 다르다.)
    - dp를 구할 때 랭킹 차이의 합을 이용해야 하며, 시합 후에는 작은 값(= 높은 순위)이 올라오게 된다. (구간에서 최종적으로 승리한 사람)
    만약 len >= 3이게 될 시 각 범위에서는 이전에 시합을 치뤄 승리하게 된 순위(= lval, rval)가 존재할 것이며, dp[l][r]을 구하기 위해서는 이 두 순위를 대결시켜야 한다.
    두 순위는 각 범위에서의 최솟값일 것이다. 이를 고려해 각 범위에서의 최솟값을 저장할 mn을 만들어준다.
    0) mn을 만들어 각 범위에서 가장 작은 값을 저장함.
    이후 범위를 len에 맞춰 탐색을 진행.
    1) 1인 경우
    - 구간을 나눌 방법은 하나이며, 이는 서로 인접한 값의 차이가 가장 작은 값이 되므로 dp에 저장.
    이후 l, r값을 변경해가며 나머지 범위를 탐색.
    2) 2인 경우
    - 구간을 나눠주며, [1][2]+[3], [1]+[2][3]의 결과중 가장 작은 값을 dp에 저장.
    이후 l, r값을 변경해가며 나머지 범위를 탐색.
    3) ~n까지 2)를 반복해줌. 최종적으로 [0][n-1]이두 선수위 랭킹 차이의 총 합의 최솟값이 된다.
    etc.)
    - 그리디로 풀 줄 몰라서 DP로..
    - 11066 파일 합치기와 비슷한 문제.
    - mn을 안만들고 비교 때마다 lval, rval을 구해줬는데 시간이 오래걸림. (TLE는 아녔음)
    참고)
    - 설명이 잘못됬다는걸 몰라서 몇시간을 날려버린 문제.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890
#define MAX 256 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 1 ≤ n ≤ 256
    cin >> n;
    vector<int> arr(n);
    for (auto &elem : arr)
        cin >> elem;

    int dp[MAX][MAX]; // dp[i][j] = 13일 경우, 구간 [i, j]에서의 랭킹 차이의 총 합의 최솟값 (= ans)
    for (int i = 0; i < MAX; i++)
        fill(dp[i], dp[i] + MAX, 0);

    int mn[MAX][MAX]; // 구간에서의 최솟값. (mn[1][3] = 2일 경우, 1~3에서 가장 작은 값은 2 (= 1번과 2번, 3번이 시합을 통해 올라온 순위는 2위이며, 이는 1~3에서 가장 높은 순위임))
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (i == j)
                mn[i][i] = arr[i];
            else
                mn[i][j] = min(mn[i][j - 1], arr[j]);

    for (int len = 1; len < n; len++)
        for (int l = 0; l < n - len; l++)
        {
            int r = l + len;

            dp[l][r] = INF;
            for (int mid = l; mid < r; mid++)
            {
                int lval = mn[l][mid], rval = mn[mid + 1][r]; // 각 구간에서의 가장 작은 값 (= 각 구간에서 토너먼트를 통해 올라온 순위)
                dp[l][r] = min(dp[l][r], dp[l][mid] + dp[mid + 1][r] + abs(lval - rval));
            }
        }

    cout << dp[0][n - 1];
}

// 1 1
// ans: 0

// 3 2 1 3
// ans: 3