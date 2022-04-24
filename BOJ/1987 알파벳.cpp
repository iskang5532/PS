// 2022-04-24
// 1987 알파벳
// https://www.acmicpc.net/problem/1987
/*
    sol.1) BFS (216,800KB, 896ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자를 숫자로 바꾼 후 board에 저장.
    이는 이전에 지나친 알파벳을 비트마스킹으로 저장할 것이기 때문.
    - 구조체 Info에 위치 (y, x)와 이전에 지나친 알파벳을 저장할 bit. (bit & i == true일 경우, i번째 알파벳을 지나침)
    - (y, x)까지 이동하면서 지나친 칸의 수를 저장할 dist.
    - (0, 0)에서부터 도달 가능한 모든 칸까지의 거리를 구한 후, dist의 값을 모두 확인하여 가장 큰 값을 출력.
    etc.) dist를 구조체 안에 선언한 후 큐에 넣는 식으로 할 경우 MLE.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 23

constexpr int dy[] = {-1, 0, 1, 0};
constexpr int dx[] = {0, 1, 0, -1};

int n, m; // 1 ≤ n, m ≤ 20
int board[MAX][MAX];

struct Info
{
    int y, x, bit; // (y, x), 알파벳 방문 여부 bit
};

int bfs()
{
    queue<Info> q;
    q.push({0, 0, board[0][0]});

    int dist[MAX][MAX]{};
    dist[0][0] = 1;

    while (q.size())
    {
        auto [y, x, bit] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            auto [ny, nx] = pii{y + dy[d], x + dx[d]};

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (bit & board[ny][nx]) // 해당 알파벳을 지나친 적이 있는 경우
                continue;
            if (dist[ny][nx] > dist[y][x] + 1)
                continue;

            q.push({ny, nx, bit | board[ny][nx]});
            dist[ny][nx] = dist[y][x] + 1;
        }
    }

    int ret = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            ret = max(ret, dist[i][j]);

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            board[i][j] = 1 << (c - 'A');
        }

    cout << bfs();
}

/*
    sol.2) DFS (2,024KB, 388ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자를 숫자로 바꾼 후 board에 저장.
    이는 이전에 지나친 알파벳을 비트마스킹으로 저장할 것이기 때문.
    - (0, 0)에서부터 도달 가능한 모든 칸까지의 거리를 구한 후, ans에 가장 큰 값을 저장.
    이후 ans 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 23

constexpr int dy[] = {-1, 0, 1, 0};
constexpr int dx[] = {0, 1, 0, -1};

int n, m; // 1 ≤ n, m ≤ 20
int board[MAX][MAX];
int ans;

void dfs(int y, int x, int bit, int dep)
{
    ans = max(ans, dep);

    for (int d = 0; d < 4; d++)
    {
        auto [ny, nx] = pii{y + dy[d], x + dx[d]};

        if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
            continue;
        if (bit & board[ny][nx]) // 해당 알파벳을 지나친 적이 있는 경우
            continue;

        dfs(ny, nx, bit | board[ny][nx], dep + 1);
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            char c;
            cin >> c;
            board[i][j] = 1 << (c - 'A');
        }

    dfs(0, 0, board[0][0], 1);
    cout << ans;
}