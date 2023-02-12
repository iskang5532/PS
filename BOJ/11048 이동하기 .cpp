// 2023-02-08
// 11048 이동하기
// https://www.acmicpc.net/problem/11048
/*
    DP (9,880KB, 80ms)
    시간 복잡도: ?
    풀이)
    - dp를 이용하여 (y, x)에 도달할 때 모을 수 있는 사탕 개수의 최댓값을 저장.
    - 현재 위치가 (y, x)일 때, 다음에 도달할 수 있는 세 위치에 놓인 각각의 사탕을 이용하여 최댓값을 구함.
    (y, x)까지의 최댓값 dp[y][x]와 (ny, nx)에 놓인 사탕을 더한 값과 이전에 구한 최댓값 dp[ny][nx]를 비교하여 dp에 저장.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 1'003 // max m, n

int n, m; // 1 ≤ n, m  ≤ 1,000
int board[MAX][MAX];
int dp[MAX][MAX];

bool OOB(int ny, int nx) { return !(0 <= ny && ny < n) || !(0 <= nx && nx < m); }

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    dp[0][0] = board[0][0];
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            for (const auto &[dy, dx] : {pii{0, 1}, pii{1, 1}, pii{1, 0}})
            {
                auto [ny, nx] = pii{y + dy, x + dx}; // 다음 위치
                if (OOB(ny, nx))
                    continue;

                dp[ny][nx] = max(dp[ny][nx], dp[y][x] + board[ny][nx]); // 이전에 구한 최댓값과 비교
            }

    cout << dp[n - 1][m - 1];
}