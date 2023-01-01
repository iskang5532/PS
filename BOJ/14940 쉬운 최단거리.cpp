// 2022-12-27
// 14940 쉬운 최단거리
// https://www.acmicpc.net/problem/14940
/*
    BFS (9,884KB, 44ms)
    시간 복잡도: ?
    풀이)
    - 지도를 board에 저장하며, 시작 지점을 st에 저장.
    - bfs를 이용하여 시작 지점에서 출발하여 도달할 수 있는 위치의 거리를 dist에 저장.
    최단 거리를 구해야 하므로, dist에 저장된 기존 값이 아닐 경우, 거리를 갱신하지 않는다.
    또한, board에 0인 부분은 도달할 수 없는 곳이므로 제외한다.
    - dist에 저장된 값을 출력한다.
    만약 도달한 적이 있을 경우, 값을 출력한다.
    만약 도달한 적이 없으면서 땅인 경우, -1을 출력한다.
    만약 도달한 적이 없으면서 땅이 아닌 경우, 0을 출력한다.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define INF 0x3f3f3f3f
#define MAX 1'003 // max n, m

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

int n, m; // 지도의 크기
int board[MAX][MAX];
int dist[MAX][MAX]; // dist[i][j] = k일 경우, 시작점에서 {i, j}까지의 거리는 k

bool OOB(int ny, int nx) { return !(0 <= ny && ny < n) || !(0 <= nx && nx < m); }

void bfs(const pii &st)
{
    queue<pii> q;
    q.push(st);

    fill(&dist[0][0], &dist[0][0] + MAX * MAX, INF);
    dist[st.first][st.second] = 0; // 시작점의 거리

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();
        for (int d = 0; d < 4; d++)
        {
            auto [ny, nx] = pii{y + dy[d], x + dx[d]};
            if (OOB(ny, nx))
                continue;
            if (dist[ny][nx] != INF || board[ny][nx] == 0) // 도달한 적이 있거나 갈 수 없는 곳인 경우
                continue;

            q.push({ny, nx}), dist[ny][nx] = dist[y][x] + 1;
        }
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    pii st; // 시작 지점
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 2)
                st = {i, j};
        }

    bfs(st);

    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < m; j++)
            cout << (dist[i][j] != INF ? dist[i][j]                   // 도달한 적이 있을 경우
                                       : (board[i][j] != 0 ? -1 : 0)) // 땅인 부분에 도달할 수 없는 경우
                 << ' ';
}