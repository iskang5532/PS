// 2023-03-13
// 16918 봄버맨
// https://www.acmicpc.net/problem/16918
/*
    구현 (2,180KB, 36ms)
    시간 복잡도: ?
    풀이)
    - 0초: 폭탄이 설치된 시간을 저장할 board[][]. 단, 설치된 폭탄이 없을 경우 -1로 표시. (= EMPTY)
    - 1초: 아무것도 하지 않음.
    - 2초: 설치되지 않은 모든 공간에 폭탄을 설치.
    - 3초: 3초 전에 설치된 모든 폭탄을 터트림.
     현재 위치의 폭탄이 3초 전에 설치된 폭탄일 경우, 인접한 네 방향의 폭탄을 터트림
     단, 인접한 폭탄 또한 3초 전에 설치된 폭탄일 경우 제외. (터트릴 경우 탐색에서 제외되므로 해당 폭탄과 인접한 폭탄을 터트릴 수 없음)
    - 4초 이후부터는 2초와 3초를 반복.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 203 // max r, c
#define EMPTY -1

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

int r, c, n;         // 크기 r, c, 시간 n (1 ≤ r, c, n ≤ 200)
int board[MAX][MAX]; // board[y][x] = t일 경우, (y, x)의 폭탄은 t초에 설치됨 (단, -1일 경우 폭탄은 존재하지 않음)

bool OOB(int ny, int nx) { return !(0 <= ny && ny < r) || !(0 <= nx && nx < c); }

void created_bomb(int t) // 빈 공간에 폭탄 생성
{
    for (int y = 0; y < r; y++)
        for (int x = 0; x < c; x++)
            if (board[y][x] == EMPTY)
                board[y][x] = t;
}

void boom(int t) // 3초 전에 설치된 폭탄을 터트림
{
    int k = t - 3;
    for (int y = 0; y < r; y++)
        for (int x = 0; x < c; x++)
            if (board[y][x] == k) // 터트려야 하는 폭탄일 경우, 인접한 네 방향의 폭탄을 터트림 (단, k와 같을 경우 제외)
            {
                board[y][x] = EMPTY;
                for (int d = 0; d < 4; d++)
                {
                    int ny = y + dy[d], nx = x + dx[d];
                    if (OOB(ny, nx) || board[ny][nx] == k) // k초를 가진 폭탄을 제외. 그래야 해당 폭탄과 인접한 다른 폭탄을 터트릴 수 있음
                        continue;
                    board[ny][nx] = EMPTY;
                }
            }
}

int main()
{
    FAST_IO;

    cin >> r >> c >> n;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
        {
            char c;
            cin >> c;
            board[i][j] = (c == 'O') ? 0 // 0초
                                     : EMPTY;
        }

    for (int t = 2; t <= n; t++)
        !(t & 1) ? created_bomb(t) // 짝수 시간
                 : boom(t);        // 홀수 시간

    for (int y = 0; y < r; y++, cout << endl)
        for (int x = 0; x < c; x++)
            cout << ((board[y][x] == EMPTY) ? '.' : 'O');
}