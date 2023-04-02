// 2023-03-31
// 10469 사이 나쁜 여왕들
// https://www.acmicpc.net/problem/10469
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 여왕의 위치를 v에 저장.
    - v에 저장된 위치를 기준점으로 사용하여 각 방향에 여왕이 존재하는지 확인.
    만약 존재할 경우 invalid 출력.
    방향은 총 여섯개인 수직과 수평, 북서 방향과 북동, 남동, 남서 방향을 탐색.
    - 입력된 여왕의 수가 8이 아닐 경우 또한 invalid
    etc.) 이상한 문제
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 8
#define QUEEN '*'

vector<pii> v;
char board[MAX][MAX];

bool isValid(int y, int x)
{
    for (int ny = 0; ny < MAX; ny++)
        if (ny != y && board[ny][x] == QUEEN)
            return false;
    for (int nx = 0; nx < MAX; nx++)
        if (nx != x && board[y][nx] == QUEEN)
            return false;
    for (int ny = y - 1, nx = x - 1; ny >= 0 && nx >= 0; ny--, nx--) // 북서
        if (board[ny][nx] == QUEEN)
            return false;
    for (int ny = y - 1, nx = x + 1; ny >= 0 && nx < MAX; ny--, nx++) // 북동
        if (board[ny][nx] == QUEEN)
            return false;
    for (int ny = y + 1, nx = x + 1; ny < MAX && nx < MAX; ny++, nx++) // 남동
        if (board[ny][nx] == QUEEN)
            return false;
    for (int ny = y + 1, nx = x - 1; ny < MAX && nx >= 0; ny++, nx--) // 남서
        if (board[ny][nx] == QUEEN)
            return false;

    return true;
}

int main()
{
    FAST_IO;

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == QUEEN)
                v.push_back({i, j});
        }

    bool valid = true;
    for (const auto &[y, x] : v)
        valid &= isValid(y, x);

    cout << ((v.size() == 8 && valid) ? "valid" : "invalid");
}