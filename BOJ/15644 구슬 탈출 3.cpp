// 2023-04-01
// 15644 구슬 탈출 3
// https://www.acmicpc.net/problem/15644
/*
    구현, bfs (2,052KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 구슬의 방문 여부를 visited에 저장. (보드의 크기가 작으므로 가능)
    - bfs를 이용하여 빨간 구슬이 제한 횟수 안에 들어가는 방법을 구함.
    - 구슬을 d 방향으로 움직이게 하는 함수 push_bead()를 구현.
    구슬은 다른 구슬이 막고 있을 경우 해당 위치로는 움직일 수 없음.
    먼저 움직이는 구슬이 나머지 구슬에 막혀 움직이지 못하는 현상이 있을 수 있으므로, 총 세 번의 수행으로 두 구슬 모두 방향 d로 움직임.
    만약 구슬이 출구에 도달할 경우, 해당 구슬의 위치는 출구로 고정.
    - 이동한 빨간 구슬과 파란 구슬의 위치를 이용.
    만약 빨간 구슬이 출구에 위치하면서 파란 구슬은 출구에 위치하지 않을 경우, 방향과 횟수를 추가하여 반환.
    각 구슬의 위치가 이전에 있었던 경우, 현재 상황을 제외. (= 큐에 넣지 않음)
    파란 구슬이 출구에 위치하거나 현재까지의 수행 횟수가 10회인 경우, 현재 상황을 제외.
    etc.) 푼 적이 있던 듯싶었는데 13460와 같은 문제였음.
    - 두 번의 수행으로 각 구슬을 움직인 후, 같은 위치일 경우 방향에 맞춰 떼어내는 풀이도 가능. 이게 더 좋은듯
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 13 // max n, m
#define WALL '#'
#define y first
#define x second

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};
constexpr char dcmd[] = {'U', 'R', 'D', 'L'};

int n, m; // 보드의 크기 (3 ≤ n, m ≤ 10)
char board[MAX][MAX];
pii ext;
bool visited[MAX][MAX][MAX][MAX]; // 각 구슬의 방문 상태를 저장 (visited[1][2][3][4] = true일 경우, {1, 2}에 빨간 구슬이, {3, 4}에 파란 구슬이 이전에 위치했었음)

struct P
{
    pii red, blue; // 빨간 구슬의 위치, 파란 구슬의 위치
    int cnt = 0;   // 이동 횟수
    string cmd;
};

void push_bead(pii &bead, const pii &other, int d) // 구슬을 d 방향으로
{
    if (bead == ext)
        return;

    while (true)
    {
        auto [y, x] = bead;
        int ny = y + dy[d], nx = x + dx[d];

        if (pii{ny, nx} == ext) // 다음 위치가 출구인 경우
        {
            bead = ext;
            return;
        }
        if (pii{ny, nx} == other || board[ny][nx] == WALL) // 다음 위치에 다음 구슬이 존재하거나 벽일 경우
            return;

        bead = {ny, nx};
    }
}

pair<string, int> bfs(const P &st)
{
    queue<P> q;
    q.push(st);

    visited[st.red.y][st.red.x][st.blue.y][st.blue.x] = true;

    while (q.size())
    {
        const auto &[red, blue, cnt, cmd] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++)
        {
            pii _red = red, _blue = blue;
            push_bead(_red, _blue, d);
            push_bead(_blue, _red, d);
            push_bead(_red, _blue, d);

            if (_red == ext && _blue != ext) // 빨간 구슬만 탈출한 경우
                return {cmd + dcmd[d], cnt + 1};
            if (visited[_red.y][_red.x][_blue.y][_blue.x]) // 각 구슬의 위치가 이전에 있었던 경우
                continue;
            if (_blue == ext || cnt + 1 == 10) // 파란 구슬이 탈출하였거나 현재까지의 이동 횟수가 10회인 경우
                continue;

            visited[_red.y][_red.x][_blue.y][_blue.x] = true;
            q.push({_red, _blue, cnt + 1, cmd + dcmd[d]});
        }
    }

    return {"", -1};
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    P p;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 'R')
                p.red = {i, j};
            else if (board[i][j] == 'B')
                p.blue = {i, j};
            else if (board[i][j] == 'O')
                ext = {i, j};
        }

    auto [cmd, cnt] = bfs(p);

    if (cmd.empty())
        cout << -1;
    else
        cout << cnt << endl
             << cmd;
}