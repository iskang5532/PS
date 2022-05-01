// 2022-04-27
// 17837 새로운 게임 2
// https://www.acmicpc.net/problem/17837
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 구조체 P에 말의 정보를 저장.
    현재 말의 위치 (y, x), 방향 dir, 바로 위에 있는 말의 번호 upper, 아래에 있는 말의 번호 under. (단, 위 혹은 아래에 말이 존재하지 않을 경우 0)
    - (y, x)에 존재하는 말 중 가장 위에 있는 말의 번호를 저장할 top, (y, x)에 존재하는 말의 수를 저장할 cnt.
    - 만약 말의 다음 위치가 파랑 혹은 범위를 벗어난 곳일 경우, 방향을 회전함.
    - 말의 다음 위치(위 과정을 거친 이후)가 흰색일 경우, 말과 말 위의 모든 말을 옮김.
    - 말의 다음 위치가 빨강일 경우, 말과 말 위의 모든 말을 옮김.
    이때, 옮겨지는 말의 upper와 under의 값을 서로 교환함.
    - 말의 다음 위치가 파랑 혹은 범위를 벗어난 곳일 경우, 옮기지 않음.
    - 만약 말이 4마리 이상 존재하는 칸이 생길 경우, 턴의 번호 t를 출력.
    etc.) 8시간..
 */
#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 15

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

enum
{
    WHITE = 0,
    RED,
    BLUE
};

struct P
{
    int y, x, dir;
    int upper, under;
};

int n, k; // 체스판의 크기 n(4 ≤ n ≤ 12), 말의 개수 k(4 ≤ k ≤ 10)
int board[MAX][MAX];
P horse[MAX];
int top[MAX][MAX], cnt[MAX][MAX];

bool OOB(int y, int x) { return !(0 <= y && y < n) || !(0 <= x && x < n); }

bool Move(int cur)
{
    auto [y, x, dir, upper, under] = horse[cur];

    { // 파란색 or OOB
        auto [ny, nx] = pii{y + dy[dir], x + dx[dir]};
        if (OOB(ny, nx) || board[ny][nx] == BLUE)
            horse[cur].dir = (dir + 2) % 4, dir = horse[cur].dir;
    }

    auto [ny, nx] = pii{y + dy[dir], x + dx[dir]};
    if (OOB(ny, nx) || board[ny][nx] == BLUE)
        return false;
    else if (board[ny][nx] == WHITE)
    {
        int next = top[y][x];
        while (next != horse[cur].under)
        {
            horse[next].y = ny, horse[next].x = nx;
            cnt[y][x]--, cnt[ny][nx]++;

            next = horse[next].under;
        }

        int cur_under = horse[cur].under;
        horse[top[ny][nx]].upper = cur, horse[cur].under = top[ny][nx];

        top[ny][nx] = top[y][x], top[y][x] = cur_under;
    }
    else if (board[ny][nx] == RED)
    {
        int cur_top = top[y][x];
        int cur_under = horse[cur].under;

        int next = top[y][x];
        while (next != cur_under)
        {
            int _next = horse[next].under;

            swap(horse[next].under, horse[next].upper);
            horse[next].y = ny, horse[next].x = nx;
            cnt[y][x]--, cnt[ny][nx]++;

            next = _next;
        }

        top[y][x] = cur_under;
        horse[cur_top].under = top[ny][nx], horse[top[ny][nx]].upper = cur_top;
        top[ny][nx] = cur, horse[cur].upper = 0;
    }

    return cnt[ny][nx] >= 4;
}

int main()
{
    FAST_IO;

    cin >> n >> k;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j]; // 0은 흰색, 1은 빨간색, 2는 파란색

    for (int i = 1; i <= k; i++)
    {
        int y, x, dir;
        cin >> y >> x >> dir;
        y--, x--, dir--;

        int _dir[] = {1, 3, 0, 2};
        horse[i] = {y, x, _dir[dir]};
        top[y][x] = i, cnt[y][x]++;
    }

    bool valid = false;
    int t = 0;
    for (; t <= 1000 && !valid; t++)
        for (int i = 1; i <= k; i++)
            if (Move(i))
                valid = true;

    cout << (valid ? t : -1);
}