/* 
 * 11660 구간 합 구하기 5
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/11660
 * ETC.) 페이지의 밑에 있는 알고리즘 분류에서 '누적 합'이라 적힌 글을 보고 감을 얻음.
 * 첫 풀이는 두 좌표가 주어질 때마다 그에 맞는 값들을 더하는 식으로 풀었지만, 시간 초과.
 * 두 번째 풀이는 입력된 행렬 arr를 이용하여 dp를 만듬.
 * dp[col][row]일 때, col에서 0에서부터 row까지의 합을 나타냄.  ex) dp[2][5] == arr[2][0] + arr[2][1] + ... + arr[2][5]
 * 세 번째 풀이는 두 번째 풀이를 다듬었으며, 입력받는 행렬값을 이용해 곧바로 dp를 제작 (= 현재 코드)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 1024 + 1

int solution(const int dp[][MAX], const int y1, const int x1, const int y2, const int x2)
{
    int answer = 0;
    for (int col = y1; col <= y2; col++)
        answer += (dp[col][x2] - dp[col][x1 - 1]); // x2까지의 합에서 x1 - 1까지의 합을 빼줌 (= 원하는 범위)

    return answer;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, k; // 1 <= N <= 1024, 1 <= M <= 100k
    cin >> n >> k;

    int dp[MAX][MAX] = {0};
    for (int col = 1; col <= n; col++)
        for (int row = 1; row <= n; row++)
        {
            int num;
            cin >> num;
            dp[col][row] = dp[col][row - 1] + num; // 이전 dp값 + 입력 값
        }

    while (k--)
    {
        int y1, x1, y2, x2;
        cin >> y1 >> x1 >> y2 >> x2;
        cout << solution(dp, y1, x1, y2, x2) << endl;
    }
}