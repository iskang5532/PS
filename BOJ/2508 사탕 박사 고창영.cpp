// 2508 사탕 박사 고창영
// https://www.acmicpc.net/problem/2508
/*
    구현, 완전 탐색 (2,180KB, 12ms)
    시간 복잡도: ?
    풀이)
    - 행과 열의 크기가 작으므로 완전 탐색을 이용해 사탕의 개수를 구함.
    - 현재 칸이 'o'인 경우, 위아래와 양옆을 확인하여 사탕인지 확인.
    - 현재 칸이 'o'이면서 위아래 및 양옆이 사탕 껍질인 경우는 없으므로 중복 검사는 불필요.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 403 // max r, c

char board[MAX][MAX]; // . o < > v ^

int get_ans(int r, int c)
{
    int ret = 0;

    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
            if (board[i][j] == 'o')
            {
                if (board[i - 1][j] == 'v' && board[i + 1][j] == '^') // 세로
                    ret++;
                if (board[i][j - 1] == '>' && board[i][j + 1] == '<') // 가로
                    ret++;
            }

    return ret;
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        fill(&board[0][0], &board[0][0] + MAX * MAX, '\0');

        int r, c; // 행렬의 크기 (1 ≤ r,c ≤ 400)
        cin >> r >> c;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
                cin >> board[i][j];

        cout << get_ans(r, c) << endl;
    }
}