// 2023-01-31
// 27211 도넛 행성
// https://www.acmicpc.net/problem/27211
/*
    BFS (6,084KB, 104ms)
    시간 복잡도: ?
    풀이)
    - bfs를 이용하여 빈 공간의 개수를 파악.
    기존 문제들과 다른 점은, 영역을 벗어날 경우 반대편으로 넘어가진다는 것이다.
    즉, 다음 위치 {ny, nx}를 구할 때 나머지 연산을 이용하여 반대편 값을 구한다.
    - 모든 위치를 확인하며, 현재 위치가 빈 공간일 경우, ans++하며 인접한 모든 빈 공간을 숲으로 덮는다.
*/

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 1'003 // max n, m

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

int n, m; // 2 ≤ n, m ≤ 1,000
int board[MAX][MAX];

void bfs(int st_y, int st_x) // 빈 공간과 인접한 모든 빈 공간을 숲으로 채움
{
    queue<pii> q;
    q.push({st_y, st_x});
    board[st_y][st_x] = true; // 숲으로 덮음

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            auto [ny, nx] = pii{((n + y + dy[d]) % n), (m + x + dx[d]) % m};
            if (board[ny][nx]) // 숲일 경우
                continue;

            q.push({ny, nx}), board[ny][nx] = true;
        }
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    int ans = 0;
    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            if (!board[y][x]) // 숲이 아닐 경우 (= 빈 공간일 경우)
                ans++, bfs(y, x);

    cout << ans;
}