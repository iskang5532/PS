//  7576 토마토
// https://www.acmicpc.net/problem/7576
/*
    BFS (14,132KB, 100ms)
    시간 복잡도: ?
    풀이)
    - 입력에서 익은 토마토가 들어온 경우, 해당 위치를 큐(= q)에 저장.
    - BFS를 이용해 익지 않은 토마토까지의 거리를 구함.
    거리는 배열 dist를 선언하여 저장하며, 초깃값은 INF.
    - 만약 익지 않은 토마토까지의 거리가 INF일 경우, 모든 토마토가 모두 익지 못하는 상황이므로 -1을 출력.
    - '저장될 때부터 모든 토마토가 익어있는 상태'에 대해서는, 익지 않은 토마토의 최대 거리를 구하는 과정에서 걸러짐.
    BFS로 구한 dist를 확인하게 되는데, 익지 않은 토마토가 없으므로 ret값이 갱신될 일이 없다. 그러므로 반환값은 ret의 초깃값인 0이 된다.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 1234567890
#define MAX 1000 + 1
typedef pair<int, int> pii;
constexpr int dx[6] = {0, 1, 0, -1}; // 앞 오 뒤 왼
constexpr int dy[6] = {-1, 0, 1, 0};

int m, n; // 행 m, 열 n (2 ≤ m, n ≤ 100)
int arr[MAX][MAX];
int dist[MAX][MAX]; // dist and visited
queue<pii> q;

void bfs() // get dist
{
    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();
        for (int i = 0; i < 6; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m))
                continue;
            if (dist[ny][nx] != INF)
                continue;
            if (arr[ny][nx] == 0)
            {
                dist[ny][nx] = dist[y][x] + 1;
                q.push({ny, nx});
            }
        }
    }
}

int get_ans()
{
    int ret = 0;

    for (int _y = 0; _y < n; _y++)
        for (int _x = 0; _x < m; _x++)
            if (arr[_y][_x] == 0)
                ret = max(ret, dist[_y][_x]);

    return ret;
}

int main()
{
    FAST_IO;

    cin >> m >> n;

    fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(dist[0][0]), INF);

    for (int _y = 0; _y < n; _y++)
        for (int _x = 0; _x < m; _x++)
        {
            int k;
            cin >> k;
            arr[_y][_x] = k;
            if (k == 1)
            {
                dist[_y][_x] = 0;
                q.push({_y, _x});
            }
        }

    bfs();
    int ans = get_ans();
    ans == INF ? cout << -1 : cout << ans;
}

// 7569 토마토
// https://www.acmicpc.net/problem/7569
/*
    BFS (11,664KB, 124ms)
    시간 복잡도: ?
    풀이)
    - 입력에서 익은 토마토가 들어온 경우, 해당 위치를 큐(= q)에 저장.
    - BFS를 이용해 익지 않은 토마토까지의 거리를 구함.
    거리는 3차원 배열 dist를 선언하여 저장하며, 초깃값은 INF.
    - 만약 익지 않은 토마토까지의 거리가 INF일 경우, 모든 토마토가 모두 익지 못하는 상황이므로 -1을 출력.
    - '저장될 때부터 모든 토마토가 익어있는 상태'에 대해서는, 익지 않은 토마토의 최대 거리를 구하는 과정에서 걸러짐.
    BFS로 구한 dist를 확인하게 되는데, 익지 않은 토마토가 없으므로 ret값이 갱신될 일이 없다. 그러므로 반환값은 ret의 초깃값인 0이 된다.
    etc.) 좀 더 최적화가 가능해 보이는데, AC이므로 패스.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 1234567890
#define MAX 100 + 1
constexpr int dx[6] = {0, 1, 0, -1, 0, 0}; // 앞 오 뒤 왼 위 아
constexpr int dy[6] = {-1, 0, 1, 0, 0, 0};
constexpr int dz[6] = {0, 0, 0, 0, -1, 1};

struct P // tuple<int, int, int>
{
    int z, y, x;
};

int m, n, h; // 행 m, 열 n (2 ≤ m, n ≤ 100), 높이 h(1 ≤ h ≤ 100)
int arr[MAX][MAX][MAX];
int dist[MAX][MAX][MAX]; // dist and visited
queue<P> q;

void bfs() // get dist
{
    while (q.size())
    {
        auto [z, y, x] = q.front();
        q.pop();
        for (int i = 0; i < 6; i++)
        {
            int nz = z + dz[i];
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (!(0 <= nz && nz < h) || !(0 <= ny && ny < n) || !(0 <= nx && nx < m))
                continue;
            if (dist[nz][ny][nx] != INF)
                continue;
            if (arr[nz][ny][nx] == 0)
            {
                dist[nz][ny][nx] = dist[z][y][x] + 1;
                q.push({nz, ny, nx});
            }
        }
    }
}

int get_ans()
{
    int ret = 0;

    for (int _h = 0; _h < h; _h++)
        for (int _y = 0; _y < n; _y++)
            for (int _x = 0; _x < m; _x++)
                if (arr[_h][_y][_x] == 0)
                    ret = max(ret, dist[_h][_y][_x]);

    return ret;
}

int main()
{
    FAST_IO;

    cin >> m >> n >> h;

    fill(&dist[0][0][0], &dist[0][0][0] + sizeof(dist) / sizeof(dist[0][0][0]), INF);

    for (int _h = 0; _h < h; _h++)
        for (int _y = 0; _y < n; _y++)
            for (int _x = 0; _x < m; _x++)
            {
                int k;
                cin >> k;
                arr[_h][_y][_x] = k;
                if (k == 1)
                {
                    dist[_h][_y][_x] = 0;
                    q.push({_h, _y, _x});
                }
            }

    bfs();
    int ans = get_ans();
    ans == INF ? cout << -1 : cout << ans;
}
