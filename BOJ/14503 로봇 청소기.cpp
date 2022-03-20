// 14503 로봇 청소기
// https://www.acmicpc.net/problem/14503
/*
    구현 (2,020KB, 0ms)
    시간 복잡도: ?
    etc.) 단순 BFS인줄 알았지만 구현이었던 문제.
    참고)
    - 왼쪽으로 방향전환 참고: https://blog.naver.com/jinhan814/222081450826
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 53
#define WALL 1

constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dx[4] = {0, 1, 0, -1};

int n, m;    //세로 크기 N, 가로 크기 M (3 ≤ N, M ≤ 50)
int r, c, d; // 청소기 좌표 (r, c) 바라보는 방향 d가 주어진다.
bool board[MAX][MAX];

int solution()
{
    int y = r, x = c;

    bool visited[MAX][MAX]; // visited[i][j] = true일 경우, 좌표 (i, j)는 청소가 된 상태.
    fill(&visited[0][0], &visited[0][0] + size(visited) * size(visited[0]), false);

    int cnt = 0;
    while (true)
    {
        bool flag = true; // 후진이 필요한가?

        if (!visited[y][x])
            cnt++, visited[y][x] = true; // 현재 구역 청소
        for (int i = d + 3; i >= d; i--) // 보고 있는 방향에서부터 왼쪽으로
        {
            int nd = i % 4; // 왼쪽 방향
            auto [ny, nx] = pii{y + dy[nd], x + dx[nd]};
            if (board[ny][nx] == WALL || visited[ny][nx])
                continue;

            y = ny, x = nx, d = nd;
            flag = false;
            break;
        }
        if (flag)
        {
            int nd = (d + 2) % 4; // 후진할 장소
            auto [ny, nx] = pii{y + dy[nd], x + dx[nd]};
            if (board[ny][nx] == WALL)
                return cnt;

            y = ny, x = nx;
        }
    }

    return cnt;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    cin >> r >> c >> d;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    cout << solution();
}