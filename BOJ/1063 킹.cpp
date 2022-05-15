// 2022-05-09
// 1063 킹
// https://www.acmicpc.net/problem/1063
/*
    구현 (2,032KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 맵에 커맨드와 그에 해당하는 값을 저장한 후, 커맨드가 입력되면 값을 추출.
    - 구현 시 주의할 점
     - y는 아래서부터 1.
     - A - '0'을 하게 되면, x는 1이 아닌 0부터.
 */

#include <iostream>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 8
#define KING 1
#define ROCK 2

map<string, pii> m = {
    {"R", {0, 1}},
    {"L", {0, -1}},
    {"B", {-1, 0}},
    {"T", {1, 0}},
    {"RT", {1, 1}},
    {"LT", {1, -1}},
    {"RB", {-1, 1}},
    {"LB", {-1, -1}},
};

bool OOB(int ny, int nx) { return !(1 <= ny && ny <= MAX) || !(1 <= nx && nx <= MAX); }

int board[MAX + 3][MAX + 3];

int main()
{
    FAST_IO;

    string s1, s2, n;
    cin >> s1 >> s2 >> n;

    int x = s1[0] - 'A' + 1, y = s1[1] - '0';   // 킹의 위치
    int rx = s2[0] - 'A' + 1, ry = s2[1] - '0'; // 돌의 위치

    board[y][x] = KING, board[ry][rx] = ROCK;

    for (int i = 0; i < stoi(n); i++)
    {
        string cmd;
        cin >> cmd;

        auto [dy, dx] = m[cmd];
        auto [ny, nx] = pii{y + dy, x + dx}; // 킹의 다음 위치
        if (OOB(ny, nx))
            continue;

        if (board[ny][nx] == ROCK)
        {
            auto [nny, nnx] = pii{ny + dy, nx + dx}; // 돌의 다음 위치
            if (OOB(nny, nnx))
                continue;
            board[nny][nnx] = ROCK;
            ry = nny, rx = nnx;
        }

        board[ny][nx] = KING;
        y = ny, x = nx;
    }

    cout << char('A' + x - 1) << y << endl;
    cout << char('A' + rx - 1) << ry << endl;
}