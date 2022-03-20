// 14502 연구소
// https://www.acmicpc.net/problem/14502
/*
    sol.1) 완전탐색 + BFS (2,024KB, 56ms)
    시간 복잡도: ?
    풀이)
    - 입력시에 벽 혹은 바이러스의 위치를 각각 v1과 v2에 저장.
    이후 v1에 완전 탐색을 이용해 벽을 세울 수 있는 모든 경우의 수를 구함.
    - 구한 경우의 수에 bfs를 사용하여 바이러스를 퍼트린 후, 안전 영역의 크기를 구함.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 13

constexpr int dy[4] = {-1, 0, 1, 0}; // 상 우 하 좌
constexpr int dx[4] = {0, 1, 0, -1};

int n, m;
int board[MAX][MAX];
vector<pii> v0, v2; // 벽과 바이러스의 위치를 저장
int ans;

int bfs()
{
    int ret = 0;

    bool visited[MAX][MAX];
    fill(&visited[0][0], &visited[0][0] + size(visited[0]) * size(visited), false);

    queue<pii> q;
    for (const auto &[y, x] : v2)
        q.push({y, x}), visited[y][x] = true;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            auto [ny, nx] = pii{y + dy[i], x + dx[i]};

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (visited[ny][nx] || board[ny][nx] != 0)
                continue;

            q.push({ny, nx}), visited[ny][nx] = true;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == 0 && !visited[i][j])
                ret++;

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 0) // 빈 칸의 위치 (= 벽이 될 수 있는 위치)
                v0.push_back({i, j});
            else if (board[i][j] == 2) // 바이러스의 위치
                v2.push_back({i, j});
        }

    for (int a = 0; a < v0.size() - 2; a++) // 완전 탐색을 이용해 빈 공간 세 곳에 벽을 세움
        for (int b = a + 1; b < v0.size() - 1; b++)
            for (int c = b + 1; c < v0.size(); c++)
            {
                auto [y1, x1] = v0[a];
                auto [y2, x2] = v0[b];
                auto [y3, x3] = v0[c];

                board[y1][x1] = board[y2][x2] = board[y3][x3] = 1;
                ans = max(ans, bfs());
                board[y1][x1] = board[y2][x2] = board[y3][x3] = 0;
            }

    cout << ans;
}

/*
    sol.2) DFS + BFS (2,024KB, 272ms)
    풀이)
    - DFS를 이용해 벽을 세울 수 있는 모든 경우의 수를 구함.
    이후 BFS를 이용해 바이러스를 퍼트린 후, 안전 영역의 크기를 구함.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 13

constexpr int dy[4] = {-1, 0, 1, 0}; // 상 우 하 좌
constexpr int dx[4] = {0, 1, 0, -1};

int n, m;
int board[MAX][MAX];
vector<pii> v; // 바이러스의 위치를 저장
int ans;

int bfs()
{
    int ret = 0;

    bool visited[MAX][MAX];
    fill(&visited[0][0], &visited[0][0] + size(visited[0]) * size(visited), false);

    queue<pii> q;
    for (const auto &[y, x] : v)
        q.push({y, x}), visited[y][x] = true;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            auto [ny, nx] = pii{y + dy[i], x + dx[i]};

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (visited[ny][nx] || board[ny][nx] != 0)
                continue;

            q.push({ny, nx}), visited[ny][nx] = true;
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == 0 && !visited[i][j])
                ret++;

    return ret;
}

void dfs(int dep)
{
    if (dep == 3) // 벽이 3개 세워진 경우, bfs를 이용해 안전 영역의 크기를 구함
    {
        ans = max(ans, bfs());
        return;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == 0)
            {
                board[i][j] = 1;
                dfs(dep + 1);
                board[i][j] = 0;
            }
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 2)
                v.push_back({i, j});
        }

    dfs(0); // dfs를 이용해 임의의 빙 공간 세 곳에 벽을 세움

    cout << ans;
}