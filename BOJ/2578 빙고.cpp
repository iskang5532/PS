// 2578 빙고
// https://www.acmicpc.net/problem/2578
/*
    구현 (2,020KB, ms)
    시간 복잡도: ?
    풀이)
    - 빙고의 크기가 크지 않으므로, 사회자가 수를 부를 떄마다 빙고의 개수를 확인하는 과정을 완전 탐색으로 만들어줌.
    - 빙고에 적힌 수의 위치를 저장할 pos[]. (pos[i] = {row, col}일 때, i번째 수의 위치는 (row, col))
    - 사회자가 부른 수를 pos에 저장된 값을 이용해 해당 위치에 색을 칠함. (체크 여부를 저장할 board[][])
    1. 사회자가 i번째 값 k를 부름.
    2. board에서의 k의 위치를 pos에서 찾은 후 색을 칠함.
    3. 빙고가 몇 개 되었는지 확인. (= bingo())
    4. 빙고의 개수가 3개 미만인 경우, 사회자가 다시 값을 부름.
    만약 3개 이상인 경우, i의 값을 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 5

pii pos[MAX * MAX];   // pos[i] = {row, col}일 때, i번째 수의 위치는 (row, col)
bool board[MAX][MAX]; // board[row][col] = true일 경우, (row, col)은 불려진 번호

int bingo()
{
    int ret = 0; // 빙고의 개수

    for (int x = 0; x < MAX; x++) // 세로
    {
        bool flag = true;
        for (int y = 0; y < MAX; y++)
            if (!board[y][x])
                flag = false;
        if (flag)
            ret++;
    }
    for (int y = 0; y < MAX; y++) // 가로
    {
        bool flag = true;
        for (int x = 0; x < MAX; x++)
            if (!board[y][x])
                flag = false;
        if (flag)
            ret++;
    }
    { // 우상
        bool flag = true;
        for (int i = 0; i < MAX; i++)
            if (!board[i][i])
                flag = false;
        if (flag)
            ret++;
    }
    { // 우하
        bool flag = true;
        for (int i = 0; i < MAX; i++)
            if (!board[MAX - 1 - i][i])
                flag = false;
        if (flag)
            ret++;
    }

    return ret;
}

int main()
{
    FAST_IO;

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
        {
            int k;
            cin >> k;
            pos[k - 1] = {i, j};
        }

    int ans;
    for (int i = 1; i <= MAX * MAX; i++)
    {
        int k;
        cin >> k;

        auto [y, x] = pos[k - 1];
        board[y][x] = true;

        if (bingo() >= 3)
        {
            ans = i;
            break;
        }
    }

    cout << ans;
}