// 2022-11-05
// 2115 갤러리
// https://www.acmicpc.net/problem/2115
/*
    구현 (10,864KB, 20ms)
    시간 복잡도: ?
    풀이)
    - 빈 공간의 정보를 저장할 info.
    info에는 빈 공간과 인접한 벽의 위치 temp와 그림을 배치한 위치 data를 저장.
    - 구한 info를 이용하여 배치할 수 있는 그림의 개수를 구함.
    - 임의의 빈 공간을 기준으로 네 방향을 탐색하여 인접한 빈 공간을 탐색.
    이때, 탐색하는 위치에 따라 그림을 배치할 위치가 달라짐에 신경 써야 함. (dg[]에 값을 저장)
    바라보는 방향의 좌측 벽과 우측 벽에 그림을 놓을 수 있음.
    - 그림을 배치할 길이가 되면서 앞서 그림을 배치한 적이 없을 경우, 그림을 배치. (ans++)
    참고) 어렵게 푼 기분
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 1'003 // max n, m
#define WALL 'X'

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

struct P
{
    int temp = 0; // 사용 가능한 공간
    int data = 0; // 그림이 사용중인 공간
};

int n, m; // 세로 n, 가로 m (1 ≤ n, m ≤ 1,000)
char board[MAX][MAX];
P info[MAX][MAX]; // 빈 공간의 정보를 저장

bool OOB(int ny, int nx) { return !(0 <= ny && ny < n) || !(0 <= nx && nx < m); }

void get_info() // 빈 공간과 인접한 벽을 info에 저장
{
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            if (board[y][x] != WALL)
                for (int d = 0; d < 4; d++)
                {
                    auto [ny, nx] = pii{y + dy[d], x + dx[d]};
                    if (OOB(ny, nx))
                        continue;

                    if (board[ny][nx] == WALL)
                        info[y][x].temp |= 1 << d;
                }
}

int get_ans()
{
    int ret = 0; // 배치할 수 있는 그림의 위치

    enum
    {
        TOP,
        RIGHT,
        BOT,
        LEFT,
    };
    constexpr int dg[] = {RIGHT, BOT, LEFT, TOP};

    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
        {
            if (board[y][x] == WALL)
                continue;
            for (int d = 0; d < 4; d++)
            {
                auto [ny, nx] = pii{y + dy[d], x + dx[d]};
                if (OOB(ny, nx) || board[ny][nx] == WALL)
                    continue;

                for (int i = 0; i < 2; i++) // 진행 방향의 양 옆을 확인 (= 좌측 벽과 우측 벽)
                {
                    // d == 0 or 2 ? dg = 1, 3  [0][2]
                    // d == 1 or 3 ? dg = 0, 2  [1][3]
                    int dir = 1 << dg[d % 2 + (i * 2)]; // 빈 공간에서 그림을 배치할 위치
                    if (info[y][x].data & dir || info[ny][nx].data & dir) // 이미 그림이 놓여 있는 경우
                        continue;
                    if (info[y][x].temp & dir && info[ny][nx].temp & dir) // 그림을 배치할 수 있을 경우 (길이가 2 이상)
                        ret++, info[y][x].data |= dir, info[ny][nx].data |= dir;
                }
            }
        }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            cin >> board[y][x];

    get_info();
    cout << get_ans();
}