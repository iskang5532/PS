// 2022-05-07
// 1347 미로 만들기
// https://www.acmicpc.net/problem/1347
/*
    구현 (2,264KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 배열의 크기를 크게 잡은 후, 중간 지점에서부터 입력을 받음.
    - 출력할 범위 (y1, x1), (y2, x2)를 구하기 위해 board를 갱신하면서 범위 또한 갱신시킴.
    현재 위치를 (y, x)라 할 때, y < y1, x < x1, y1 < y, x1 < x일 때 갱신.
    etc.) 정사각형으로 출력하는줄 알아서 오래걸렸던 문제 (만약 정사각형이라면 어떻게?)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 500

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

char board[MAX][MAX];

int main()
{
    FAST_IO;

    fill(&board[0][0], &board[0][0] + MAX * MAX, '#');

    int y = 100, x = 100, dir = 2;
    board[y][x] = '.';

    int n;
    cin >> n;

    int y1 = 100, x1 = 100, y2 = 100, x2 = 100;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;

        if (c == 'R')
            dir = (dir + 1) % 4;
        else if (c == 'L')
            dir = (dir + 3) % 4;
        else if (c == 'F')
        {
            y += dy[dir], x += dx[dir];
            board[y][x] = '.';

            y1 = min(y1, y), x1 = min(x1, x), y2 = max(y2, y), x2 = max(x2, x);
        }
    }

    for (int y = y1; y <= y2; y++, cout << endl)
        for (int x = x1; x <= x2; x++)
            cout << board[y][x];
}