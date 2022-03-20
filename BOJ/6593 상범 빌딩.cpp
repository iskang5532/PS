// 6593 상범 빌딩
// https://www.acmicpc.net/problem/6593
/*
    BFS (2,212KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 3차원 배열을 이용한 bfs.
    - 시작점에서부터 목적지까지 bfs를 이용하여 도달할 수 있는지를 구함.
    만약 도달할 수 있다면 거리를 출력.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 0x7fffffff
#define MAX 33

constexpr int dz[6] = {0, 0, 0, 0, -1, 1}; // 북 동 남 서 상 하
constexpr int dy[6] = {-1, 0, 1, 0, 0, 0};
constexpr int dx[6] = {0, 1, 0, -1, 0, 0};

struct P
{
    int z, y, x;
    friend bool operator==(const P &p1, const P &p2) { return p1.z == p2.z && p1.y == p2.y && p1.x == p2.x; };
};

int l, r, c; // 층 l, 행 r, 열 c (1 ≤ l, r, c ≤ 30)
char board[MAX][MAX][MAX];

int bfs(P st, P ed)
{
    int dist[MAX][MAX][MAX];
    fill(&dist[0][0][0], &dist[0][0][0] + MAX * MAX * MAX, 0);

    queue<P> q;
    q.push(st);
    dist[st.z][st.y][st.x] = 0;

    int ans = 0;
    while (q.size())
    {
        auto [z, y, x] = q.front();
        q.pop();

        for (int i = 0; i < 6; i++)
        {
            auto [nz, ny, nx] = P{z + dz[i], y + dy[i], x + dx[i]};
            if (P{nz, ny, nx} == ed)
                return dist[z][y][x] + 1;

            if (!(0 <= nz && nz < l) || !(0 <= ny && ny < r) || !(0 <= nx && nx < c)) // OOB
                continue;
            if (dist[nz][ny][nx] || board[nz][ny][nx] == '#') // 도달한 적이 있거나 벽일 경우
                continue;

            q.push({nz, ny, nx}), dist[nz][ny][nx] = dist[z][y][x] + 1;
        }
    }

    return INF;
}

int main()
{
    FAST_IO;

    while (cin >> l >> r >> c)
    {
        if (!l && !r && !c)
            break;

        P st, ed;
        for (int i = 0; i < l; i++)
            for (int j = 0; j < r; j++)
                for (int k = 0; k < c; k++)
                {
                    cin >> board[i][j][k]; //  '#': 금, '.': 빈 칸,  'S': 시작, 'E': 탈출
                    if (board[i][j][k] == 'S')
                        st = {i, j, k};
                    else if (board[i][j][k] == 'E')
                        ed = {i, j, k};
                }

        int ans = bfs(st, ed);
        if (ans == INF)
            cout << "Trapped!" << endl;
        else
            cout << "Escaped in " << ans << " minute(s)." << endl;
    }
}