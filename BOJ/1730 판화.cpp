// 1730 판화
// https://www.acmicpc.net/problem/1730
/*
    구현, 비트마스킹 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 비트를 이용하여 위치 (y, x)의 상태를 저장할 board. (board[i][j] = k일 경우, (i, j)의 상태는 k (0b00 = '.', 0b01 = '|', 0b10 = '-', 0b11 = '+'))
    - 'U'와 'D'은 첫 번째 비트, 'L'과 'R'은 두 번쨰 비트를 사용함.
    만약 'L'이 입력됐을 경우, board[y][x]의 두 번째 비트를 켜줌.
    같은 위치에 'U'가 입력됐을 경우, board[y][x]의 첫 번째 비트를 켜줌. (이 때의 출력은 '+')
    - 모든 칸을 탐색하며 비트에 맞는 값을 출력함.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 13

constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dx[4] = {0, 1, 0, -1};

int n;               // 목판의 크기 N (2 ≤ N ≤ 10)
int board[MAX][MAX]; // board[i][j] = k일 경우, (i, j)의 상태는 k (0b00 = '.', 0b01 = '|', 0b10 = '-', 0b11 = '+')

void moved(int &y, int &x, int i)
{
    const auto &[ny, nx] = pii{y + dy[i], x + dx[i]};
    if (!(0 <= ny && ny < n) || !(0 <= nx && nx < n)) // OOB
        return;

    board[y][x] |= 1 << (i & 1); // 적절한 비트를 켜줌
    board[ny][nx] |= 1 << (i & 1);

    y = ny, x = nx; // 다음 위치로 이동
}

int main()
{
    FAST_IO;

    cin >> n;
    string s;
    cin >> s;

    int y = 0, x = 0;
    for (const auto &cmd : s)
    {
        int i;
        if (cmd == 'U') // odd
            i = 0;
        else if (cmd == 'R') // even
            i = 1;
        else if (cmd == 'D')
            i = 2;
        else if (cmd == 'L')
            i = 3;

        moved(y, x, i);
    }

    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < n; j++)
            if (board[i][j] == 0)
                cout << '.';
            else if (board[i][j] == 0b11)
                cout << '+';
            else if (board[i][j] == 0b01)
                cout << '|';
            else if (board[i][j] == 0b10)
                cout << '-';
}