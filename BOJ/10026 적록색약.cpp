// 10026 적록색약
// https://www.acmicpc.net/problem/10026
/*
    BFS (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 적록색약이 아닌 사람이 봤을 때의 구역의 개수 a, 적록색약인 사람이 봤을 때의 구역의 수 b
    - 2중 for문을 이용해 (i, j)의 색상을 기준으로 인접한 영역의 색상과 비교하여 구역을 탐색.
    두 종류의 사람이 존재하므로, bfs를 두 종류로 나눴음.
    적록색약인 사람인 경우, (i, j)의 값이 'R'이면서 인접한 값이 'G'이거나, 값이 'G'이면서 인접한 값이 'R'일 때를 한 영역으로 인식시키도록 함.
    - 해당 위치에 방문한 적이 있는지를 기록할 visited. (두 종류가 있으므로, 이 또한 a와 b가 존재)
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 103

constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dx[4] = {0, 1, 0, -1};

int n; // 1 ≤ N ≤ 100
char board[MAX][MAX];
bool visited_a[MAX][MAX], visited_b[MAX][MAX];
int a, b; // 적록색약이 아닌 사람이 봤을 때의 구역의 개수 a, 적록색약인 사람이 봤을 때의 구역의 수 b

void bfs_a(int y, int x)
{
    queue<pii> q;
    q.push({y, x}), visited_a[y][x] = true;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            auto [ny, nx] = pii{y + dy[i], x + dx[i]};

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < n)) // OOB
                continue;
            if (visited_a[ny][nx])
                continue;

            if (board[y][x] == board[ny][nx])
                q.push({ny, nx}), visited_a[ny][nx] = true;
        }
    }
}

void bfs_b(int y, int x)
{
    queue<pii> q;
    q.push({y, x}), visited_b[y][x] = true;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            auto [ny, nx] = pii{y + dy[i], x + dx[i]};

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < n)) // OOB
                continue;
            if (visited_b[ny][nx])
                continue;

            if (board[y][x] == board[ny][nx] ||
                board[y][x] == 'R' && board[ny][nx] == 'G' || board[y][x] == 'G' && board[ny][nx] == 'R')
                q.push({ny, nx}), visited_b[ny][nx] = true;
        }
    }
}

int main()
{
    FAST_IO;

    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (!visited_a[i][j])
                a++, bfs_a(i, j);

            if (!visited_b[i][j])
                b++, bfs_b(i, j);
        }

    cout << a << ' ' << b;
}