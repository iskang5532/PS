// 2573 빙산
// https://www.acmicpc.net/problem/2573
/*
    구현, BFS (2,816KB, 128ms)
    시간 복잡도: ?
    풀이)
    - 빙산을 녹이는 과정과 빙산이 두 개로 나눠졌거나 녹았는지를 확인하는 과정으로 나눔.
    1. 빙산을 녹이는 과정 melt()는 완전 탐색을 이용해 해당 빙산 주변 바닷물의 개수만큼 높이를 빼준다.
    2. 빙산이 모두 녹았는지 혹은 두 개로 나눠졌는지 탐색하는 과정 isValid()는 완전 탐색 및 BFS를 이용해준다.
    - 임의의 빙산 (y, x)를 기준으로 BFS를 이용해 해당 빙산과 이어져 있는 다른 빙산을 탐색하여 visited에 저장.
    이후 완전 탐색을 이용해 모든 위치를 확인하며, 빙산이지만 visited가 아닐 경우 빙산의 개수는 2개 이상.
    - 만약 (y, x)가 존재하지 않을 경우, 빙산이 모두 녹았으므로 0을 출력.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 303
using ll = long long;
using pii = pair<int, int>;

constexpr int dy[4] = {-1, 0, 1, 0}; // 상 우 하 좌
constexpr int dx[4] = {0, 1, 0, -1};

int n, m; // 3 ≤ n, m ≤ 300
vector<vector<int>> board(MAX, vector<int>(MAX));
bool melted; // 빙산이 모두 녹았는지를 저장 (true: 모두 녹음)

void melt()
{
    vector<vector<int>> ret = board;
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            if (board[y][x] > 0) // 빙산인가?
                for (int i = 0; i < 4; i++)
                {
                    auto [ny, nx] = pii{y + dy[i], x + dx[i]};
                    if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                        continue;

                    if (board[ny][nx] <= 0) // 주변이 바다인가?
                        ret[y][x]--;
                }

    board = move(ret);
}

pii get_ice() // 임의의 빙산의 위치를 구함
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] > 0)
                return {i, j};

    return {INF, INF};
}

bool isValid() // 빙산이 존재하면서 하나인가?
{
    auto [y, x] = get_ice(); // 임의의 빙산
    if (y == INF && x == INF)
    {
        melted = true;
        return false;
    }

    queue<pii> q;
    bool visited[MAX][MAX];
    fill(&visited[0][0], &visited[0][0] + sizeof(visited) / sizeof(visited[0][0]), false);

    q.push({y, x});
    visited[y][x] = true;
    while (q.size()) // BFS를 이용해 임의의 빙산과 이어져 있는 모든 빙산을 탐색
    {
        auto [y, x] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            auto [ny, nx] = pii{y + dy[i], x + dx[i]};
            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (visited[ny][nx])
                continue;
            if (board[ny][nx] <= 0)
                continue;

            q.push({ny, nx}), visited[ny][nx] = true;
        }
    }

    for (int i = 0; i < n; i++) // 빙산이 두 개로 나눠졌는지 확인
        for (int j = 0; j < m; j++)
            if (board[i][j] > 0 && !visited[i][j])
                return false;

    return true;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j]; //  0 ≤ k ≤ 10

    int ans = 0;
    for (int t = 1;; t++)
    {
        melt(); // 빙산을 녹임

        if (!isValid()) // 빙산이 존재하면서 하나인지를 확인
        {
            ans = (melted ? 0 : t);
            break;
        }
    }

    cout << ans;
}