// 3190 뱀
// https://www.acmicpc.net/problem/3190
/*
    구현, 큐 (2,068KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 현재 위치에 사과의 여부를 저장할 apple[][]. (apple[i][j] = true일 경우, (i, j)에는 사과가 존재)
    - 방향 전환을 저장할 check[]. (check[t] = d(1 or 3)일 경우, t초 이후 d로 방향 전환을 수행)
    - 해당 위치에 꼬리가 존재하는지를 저장할 be[][]. (be[i][j] = true일 경우, (i, j)에는 꼬리가 존재)
    - 현재 위치를 저장할 cur, 방향을 저장할 dir.
    - 각 시간마다 뱀을 이동시킴.
    만약 이동한 위치에 사과가 있을 경우, 사과를 없앰.
    만약 이동한 위치에 사과가 없을 경우, 꼬리를 없앰.
    - check[t]에 값이 존재(!= 0)할 경우, 방향을 전환함.
    - t가 10,000초가 되거나, 뱀이 벽 혹은 꼬리에 부딪힐 때까지 반복.
    etc.)
    - 이동할 위치에 꼬리가 있지만 이동 시에 꼬리가 없어지는 경우는 게임 오버인듯?
    - x가 같은 경우는 없는듯
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103
#define RIGHT 1

constexpr int dy[4] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[4] = {0, 1, 0, -1};

struct pii
{
    int t, d;
};

bool apple[MAX][MAX]; // apple[i][j] = true일 경우, (i, j)에는 사과가 존재
int check[10'003];    // check[t] = d(1 or 3)일 경우, t초 이후 d로 방향을 회전해야 함

int solution(int n)
{
    int t = 0, dir = RIGHT;
    pii cur = {1, 1};

    bool be[MAX][MAX]{};
    be[1][1] = true;
    queue<pii> q; // 꼬리의 위치를 저장 (FIFO)
    q.push(cur);
    while (++t <= 10'000)
    {
        auto [y, x] = cur;
        auto [ny, nx] = pii{y + dy[dir], x + dx[dir]};
        if (!(1 <= ny && ny <= n) || !(1 <= nx && nx <= n)) // OOB
            break;
        if (be[ny][nx])
            break;

        be[ny][nx] = true, q.push({ny, nx});
        cur = {ny, nx};

        if (apple[ny][nx])
            apple[ny][nx] = false;
        else // 사과가 없을 시 꼬리를 자름
        {
            auto [y, x] = q.front();
            q.pop();
            be[y][x] = false;
        }

        if (check[t]) // 회전이 필요한 경우
            dir = (dir + check[t]) % 4;
    }

    return t;
}

int main()
{
    FAST_IO;

    int n, k; // 보드의 크기 n(2 ≤ N ≤ 100) 사과의 개수 K(0 ≤ K ≤ 100)
    cin >> n >> k;
    for (int i = 0; i < k; i++)
    {
        int y, x;
        cin >> y >> x;
        apple[y][x] = true;
    }

    int l; // 뱀의 방향 변환 횟수 (1 ≤ L ≤ 100)
    cin >> l;
    for (int i = 0; i < l; i++)
    {
        int x;  // 시간 (1 ≤ x ≤ 10,000)
        char c; // 회전 방향
        cin >> x >> c;
        check[x] = c == 'L' ? 3 : 1; // 왼쪽으로 or 오른쪽으로
    }

    cout << solution(n);
}