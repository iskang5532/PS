// 1926 그림
// https://www.acmicpc.net/problem/1926
/*
    BFS (3,260KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 그림의 개수를 저장할 cnt, 가장 넓은 그림의 넓이를 저장할 mx, 탐색 여부를 저장할 visited.
    - 2중 for문을 이용해 모든 영역에 대해 탐색.
    만약 현재 영역이 1이며 탐색한 적이 없는 경우, cnt++해주며 인접한 1을 탐색.
    탐색을 완료한 영역은 visited에 저장.
    인접한 1을 찾을 때마다 현재 탐색중인 영역의 크기를 저장할 sz에 +1. (주의할 점은, 시작점을 포함시켜야 하므로 sz의 초깃값은 1)
    인접한 1이 더이상 없을 경우, mx에 저장. (단, 이전에 구한 mx보다 큰 값이어야 함)
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 503
using pii = pair<int, int>;

constexpr int dy[4] = {-1, 0, 1, 0}; // 상 우 하 좌
constexpr int dx[4] = {0, 1, 0, -1};

int n, m; // 세로 크기 n, 가로 크기 m (1 ≤ n, m ≤ 500)
int board[MAX][MAX];
bool visited[MAX][MAX];
int cnt, mx; // 그림의 개수 및 넓이

void bfs(int row, int col)
{
    int sz = 1; // 현재 영역의 넓이 (시작점을 크기에 포함시켜줌)

    queue<pii> q;
    q.push({row, col}), visited[row][col] = true;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            const auto &[ny, nx] = pii{y + dy[i], x + dx[i]};

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (visited[ny][nx] || !board[ny][nx])
                continue;

            q.push({ny, nx}), visited[ny][nx] = true;
            sz++;
        }
    }

    mx = max(mx, sz);
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    for (int row = 0; row < n; row++)
        for (int col = 0; col < m; col++)
            if (board[row][col] && !visited[row][col])
                cnt++, bfs(row, col); // get answer

    cout << cnt << endl
         << mx;
}