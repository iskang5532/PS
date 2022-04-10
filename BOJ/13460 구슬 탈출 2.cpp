// 13460 구슬 탈출 2
// https://www.acmicpc.net/problem/13460
// 2022-04-05
/*
    sol.1) 구현 (2,288KB, 0ms)
    풀이)
    - 두 개의 구슬을 네 방향으로 움직임.
    구슬을 움직일 떄, 움직이는 방향의 벽과 가까운 구슬 먼저 움직여야 함.
    이를 위해, 두 구슬 중 하나를 이동 후에 한 번 더 이동을 시킴. (둘 다 움직이기 위함)
    - 위, 아래로 움직이는 것과 왼, 오른쪽으로 움직이는 것은 같으므로 하나의 함수로 구현.
    etc.) 생각나는대로 구현
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 13

struct P
{
    pii red, blue;
    int cnt;
};

int n, m;             // 3 ≤ N, M ≤ 10
char board[MAX][MAX]; // '.': 빈 칸, '#': 벽, 'O': 구멍의 위치, 'R': 빨간 구슬, 'B': 파란 구슬
pii _red, _blue, ed;

P moved_down(const pii &red, const pii &blue, int cnt, int state = 1)
{
    pii ret_r = red, ret_b = blue;
    auto &[ret_r_y, ret_r_x] = ret_r;
    auto &[ret_b_y, ret_b_x] = ret_b;

    bool r_goal = false, b_goal = false;
    for (int y = ret_r_y; state == 1 ? y < n : y > 0; y += state)
    {
        if (board[y][ret_r_x] == '#' || !b_goal && pii{y, ret_r_x} == ret_b)
            break;
        ret_r_y = y;

        if (board[y][ret_r_x] == 'O')
            r_goal = true;
    }
    for (int y = ret_b_y; state == 1 ? y < n : y > 0; y += state)
    {
        if (board[y][ret_b_x] == '#' || !r_goal && pii{y, ret_b_x} == ret_r)
            break;
        ret_b_y = y;

        if (board[y][ret_b_x] == 'O')
            b_goal = true;
    }
    for (int y = ret_r_y; state == 1 ? y < n : y > 0; y += state)
    {
        if (board[y][ret_r_x] == '#' || !b_goal && pii{y, ret_r_x} == ret_b)
            break;
        ret_r_y = y;

        if (board[y][ret_r_x] == 'O')
            r_goal = true;
    }

    if (r_goal)
        ret_r = ed;
    if (b_goal)
        ret_b = ed;
    return {{ret_r_y, ret_r_x}, {ret_b_y, ret_b_x}, cnt + 1};
}

P moved_right(const pii &red, const pii &blue, int cnt, int state = 1)
{
    pii ret_r = red, ret_b = blue;
    auto &[ret_r_y, ret_r_x] = ret_r;
    auto &[ret_b_y, ret_b_x] = ret_b;

    bool r_goal = false, b_goal = false;
    for (int x = ret_r_x; state == 1 ? x < m : x > 0; x += state)
    {
        if (board[ret_r_y][x] == '#' || !b_goal && pii{ret_r_y, x} == ret_b)
            break;
        ret_r_x = x;

        if (board[ret_r_y][x] == 'O')
            r_goal = true;
    }
    for (int x = ret_b_x; state == 1 ? x < m : x > 0; x += state)
    {
        if (board[ret_b_y][x] == '#' || !r_goal && pii{ret_b_y, x} == ret_r)
            break;
        ret_b_x = x;

        if (board[ret_b_y][x] == 'O')
            b_goal = true;
    }
    for (int x = ret_r_x; state == 1 ? x < m : x > 0; x += state)
    {
        if (board[ret_r_y][x] == '#' || !b_goal && pii{ret_r_y, x} == ret_b)
            break;
        ret_r_x = x;

        if (board[ret_r_y][x] == 'O')
            r_goal = true;
    }

    if (r_goal)
        ret_r = ed;
    if (b_goal)
        ret_b = ed;
    return {{ret_r_y, ret_r_x}, {ret_b_y, ret_b_x}, cnt + 1};
}

int bfs()
{
    queue<P> q;
    q.push({_red, _blue, 0});

    while (q.size())
    {
        auto [red, blue, cnt] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            P p;
            if (i == 0) // 북
                p = moved_down(red, blue, cnt, -1);
            else if (i == 1) // 서
                p = moved_right(red, blue, cnt);
            else if (i == 2) // 남
                p = moved_down(red, blue, cnt);
            else if (i == 3) // 동
                p = moved_right(red, blue, cnt, -1);

            auto [n_r, n_b, n_cnt] = p;
            if (n_r == ed && n_b != ed)
                return n_cnt;

            if (!(n_r == red && n_b == blue) && blue != ed && n_cnt < 10)
                q.push({n_r, n_b, n_cnt});
        }
    }

    return -1;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j]; // '.', '#', 'O', 'R', 'B'
            if (board[i][j] == 'R')
                _red = {i, j};
            else if (board[i][j] == 'B')
                _blue = {i, j};
            else if (board[i][j] == 'O')
                ed = {i, j};
        }

    cout << bfs();
}

/*
    sol.2) 구현 (2,052KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 빨간 구슬 r과 파란 구슬 b가 네 방향으로 움직인 후의 위치를 각각 구함.
    만약 b == ed인 해당 경우를 무시.
    그 외, 만약 r == ed인 경우, 횟수를 리턴. (이때, b != ed가 성립)
    그 외, 만약 r == b인 경우, 두 구슬은 겹쳐질 수 없으므로 구슬 하나의 위치를 바꿔줌. (구슬의 위치는 구슬이 이동한 방향에 따라 결정)
    - visited를 사용하여 두 구슬이 위치한 장소를 기억한 후, 중복된 위치에 도착할 수 없도록 해줌.
    etc.) sol.1에서는 visited를 사용하지 않아도 메모리 및 시간이 여유로웠는데, sol.2는 왜?
    참고)
    - https://blog.naver.com/jinhan814/222108986832
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 13 // max n, m
#define Y first
#define X second

constexpr int dy[4] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[4] = {0, 1, 0, -1};

struct P
{
    pii red, blue;
    int cnt;
};

int n, m;             // 3 ≤ N, M ≤ 10
char board[MAX][MAX]; // '.': 빈 칸, '#': 벽, 'O': 구멍의 위치, 'R': 빨간 구슬, 'B': 파란 구슬
bool visited[MAX][MAX][MAX][MAX];

pii moved(const pii &cur, int i) // 구슬 cur를 i번 방향으로
{
    auto [y, x] = cur;
    while (true)
    {
        auto [ny, nx] = pii{y + dy[i], x + dx[i]};
        if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
            break;
        if (board[ny][nx] == '#')
            break;
        y = ny, x = nx;

        if (board[y][x] == 'O')
            break;
    }

    return {y, x};
}

int bfs(const pii &_red, const pii &_blue, const pii &ed)
{
    queue<P> q;
    q.push({_red, _blue, 0});

    while (q.size())
    {
        auto [red, blue, cnt] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            pii n_r = moved(red, i), n_b = moved(blue, i);
            if (n_b == ed)
                continue;
            else if (n_r == ed)
                return cnt + 1;

            if (n_r == n_b) // 구슬이 겹친 경우, 뗴어냄
            {
                if (i == 0)
                    red.Y < blue.Y ? n_b.Y++ : n_r.Y++;
                else if (i == 1)
                    red.X < blue.X ? n_r.X-- : n_b.X--;
                else if (i == 2)
                    red.Y < blue.Y ? n_r.Y-- : n_b.Y--;
                else if (i == 3)
                    red.X < blue.X ? n_b.X++ : n_r.X++;
            }

            if (!visited[n_r.Y][n_r.X][n_b.Y][n_b.X] && cnt + 1 < 10)
                visited[n_r.Y][n_r.X][n_b.Y][n_b.X] = true, q.push({n_r, n_b, cnt + 1});
        }
    }

    return -1;
}

int main()
{
    FAST_IO;

    cin >> n >> m;

    pii red, blue, ed;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j]; // '.', '#', 'O', 'R', 'B'
            if (board[i][j] == 'R')
                red = {i, j};
            else if (board[i][j] == 'B')
                blue = {i, j};
            else if (board[i][j] == 'O')
                ed = {i, j};
        }

    cout << bfs(red, blue, ed);
}