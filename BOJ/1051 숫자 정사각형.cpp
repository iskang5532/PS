// 2022-04-17
// 1051 숫자 정사각형
// https://www.acmicpc.net/problem/1051
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 탐색할 범위가 작으면서 정사각형만 탐색하면 되므로, 완전 탐색을 이용함.
    - 탐색할 정사각형의 크기 sz를 조절해가며 원점 (0, 0)에서부터 완전 탐색.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 53 // max n, m

int n, m; // 1 ≤ n ,m ≤ 50
char board[MAX][MAX];

int get_ans(int sz)
{
    sz -= 1;
    for (int y = 0; y < n - sz; y++)
        for (int x = 0; x < m - sz; x++)
        {
            int cur = board[y][x];
            if (board[y + sz][x] == cur && board[y][x + sz] == cur && board[y + sz][x + sz] == cur)
                return (sz + 1) * (sz + 1);
        }

    return 0;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    int ans = 0;
    for (int sz = 1; sz <= min(n, m); sz++) // 탐색할 정사각형의 크기
        ans = max(ans, get_ans(sz));

    cout << ans;
}