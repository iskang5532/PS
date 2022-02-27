// 14500 테트로미노
// https://www.acmicpc.net/problem/14500
/*
    구현 (3,204KB, 20ms)
    시간 복잡도: ?
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define MAX 550
#define t 15

int board[MAX][MAX];

int get_k(int row, int col)
{
    int ret = 0;

    { // 1
        ret = max(ret, board[row][col] + board[row][col + 1] + board[row][col + 2] + board[row][col + 3]);
        ret = max(ret, board[row][col] + board[row + 1][col] + board[row + 2][col] + board[row + 3][col]);
    }
    { // ㅁ
        ret = max(ret, board[row][col] + board[row][col + 1] + board[row + 1][col] + board[row + 1][col + 1]);
    }
    { // L
        ret = max(ret, board[row][col] + board[row + 1][col] + board[row + 2][col] + board[row + 2][col + 1]);
        ret = max(ret, board[row][col] + board[row + 1][col] + board[row + 2][col] + board[row + 2][col - 1]);

        ret = max(ret, board[row][col] + board[row][col + 1] + board[row][col + 2] + board[row - 1][col + 2]);
        ret = max(ret, board[row][col] + board[row][col + 1] + board[row][col + 2] + board[row + 1][col + 2]);

        ret = max(ret, board[row][col] + board[row - 1][col] + board[row - 2][col] + board[row - 2][col - 1]);
        ret = max(ret, board[row][col] + board[row - 1][col] + board[row - 2][col] + board[row - 2][col + 1]);

        ret = max(ret, board[row][col] + board[row][col - 1] + board[row][col - 2] + board[row + 1][col - 2]);
        ret = max(ret, board[row][col] + board[row][col - 1] + board[row][col - 2] + board[row - 1][col - 2]);
    }
    { // Z
        ret = max(ret, board[row][col] + board[row + 1][col] + board[row + 1][col + 1] + board[row + 2][col + 1]);
        ret = max(ret, board[row][col] + board[row + 1][col] + board[row + 1][col - 1] + board[row + 2][col - 1]);

        ret = max(ret, board[row][col] + board[row][col + 1] + board[row - 1][col + 1] + board[row - 1][col + 2]);
        ret = max(ret, board[row][col] + board[row][col + 1] + board[row + 1][col + 1] + board[row + 1][col + 2]);

        ret = max(ret, board[row][col] + board[row - 1][col] + board[row - 1][col - 1] + board[row - 2][col - 1]);
        ret = max(ret, board[row][col] + board[row - 1][col] + board[row - 1][col + 1] + board[row - 2][col + 1]);

        ret = max(ret, board[row][col] + board[row][col - 1] + board[row - 1][col - 1] + board[row - 1][col - 2]);
        ret = max(ret, board[row][col] + board[row][col - 1] + board[row + 1][col - 1] + board[row + 1][col - 2]);
    }
    { // ㅜ
        ret = max(ret, board[row][col] + board[row][col + 1] + board[row + 1][col + 1] + board[row][col + 2]);
        ret = max(ret, board[row][col] + board[row][col + 1] + board[row - 1][col + 1] + board[row][col + 2]);

        ret = max(ret, board[row][col] + board[row - 1][col] + board[row - 1][col + 1] + board[row - 2][col]);
        ret = max(ret, board[row][col] + board[row - 1][col] + board[row - 1][col - 1] + board[row - 2][col]);

        ret = max(ret, board[row][col] + board[row - 1][col] + board[row - 1][col + 1] + board[row - 2][col]);
        ret = max(ret, board[row][col] + board[row - 1][col] + board[row - 1][col - 1] + board[row - 2][col]);

        ret = max(ret, board[row][col] + board[row][col - 1] + board[row - 1][col - 1] + board[row][col - 2]);
        ret = max(ret, board[row][col] + board[row][col - 1] + board[row + 1][col - 1] + board[row][col - 2]);
    }

    return ret;
}

int main()
{
    FAST_IO;

    int n, m; // 4 ≤ n, m ≤ 500
    cin >> n >> m;

    for (int i = t; i < t + n; i++)
        for (int j = t; j < t + m; j++)
            cin >> board[i][j];

    int ans = 0;
    for (int i = t; i < t + n; i++)
        for (int j = t; j < t + m; j++)
            ans = max(ans, get_k(i, j));

    cout << ans;
}