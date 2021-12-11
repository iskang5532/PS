/*
    6982 Quadtrees
    분할 정복 (2,028KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/6982
    풀이)
    - 2차원 배열을 선언한 후, 입력된 문자열에 맞는 위치를 색칠함.
    - 배열의 기준점 (col, row), 범위 len.
    - 첫 문자가 p가 나와 네 구역으로 나눠진 경우, (0,0), (16,0), (0,16), (16,16)을 기준점으로 잡음.
    - str의 문자를 하나씩 확인. (현재 탐색중인 문자가 무엇인지 알기 위해 문자열의 위치(= pos)를 기억시킴)
    p가 나온 경우, len을 줄인 후 문자열 탐색.
    f가 나온 경우, (col, row)부터 (col + len, col + row)까지 색을 칠해줌.
    만약 len == 0인 경우, 더 이상 쪼갤 수 없으므로 해당 문자에 따라 배열을 칠해줌.
    - board 및 pos의 초기화를 조심.
    - len == 1이 아닌 0.
    etc.) 푸는데 오래걸린 문제.
    - 쿼드트리 구현 생각에 오래 걸림.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 32

const int dx[4] = {0, 1, 0, 1}; // 1 2
const int dy[4] = {0, 0, 1, 1}; // 3 4

int board[MAX][MAX];
int pos = 1;

void quadtree(const string &str, int row = 0, int col = 0, int len = 16)
{
    if (len == 0) // 더 이상 쪼갤 수 없음
    {
        if (str[pos] == 'f')
            board[row][col] = 1;
        return;
    }

    for (int i = 0; i < 4; i++)
    {
        char c = str[pos];
        pos++;

        int ny = row + len * dy[i];
        int nx = col + len * dx[i];

        if (c == 'p')
            quadtree(str, ny, nx, len >> 1);
        else if (c == 'f')
            for (int y = ny; y < ny + len; y++)
                for (int x = nx; x < nx + len; x++)
                    board[y][x] = 1; // 기준점에서부터 len만큼 칠해줌
    }
}

int solution(const string &str_1, const string &str_2)
{
    if (str_1.front() == 'f' || str_2.front() == 'f')
        return 1024;
    else if (str_1.front() == 'e' && str_2.front() == 'e')
        return 0;

    for (int i = 0; i < MAX; i++)
        fill(board[i], board[i] + MAX, 0);

    if (str_1.front() == 'p')
        pos = 1, quadtree(str_1);
    if (str_2.front() == 'p')
        pos = 1, quadtree(str_2);

    int ans = 0;
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            if (board[i][j] == true)
                ans++;

    return ans;
}

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
        string str_1, str_2;
        cin >> str_1 >> str_2;

        cout << "There are " << solution(str_1, str_2) << " black pixels." << endl;
    }
}
